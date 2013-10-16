#include "connection.h"
#include "net_helper.h"
#include "../utils/memory_stream.h"
#include "message_queue.h"
#include "session_manager.h"

namespace monkey{
namespace net{


monkey::net::connection::connection( boost::asio::io_service& io_service )
	: socket_(io_service)
	, current_read_bytes_(0)
	, package_len_(0)
{

}

void monkey::net::connection::start_read_head()
{
	boost::asio::async_read(socket_, boost::asio::buffer(buffer_header_),
		boost::bind(&monkey::net::connection::handle_read_head, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void monkey::net::connection::start_read()
{
	boost::asio::async_read(socket_, boost::asio::buffer(*current_read_data_, current_read_data_->size()),
		boost::bind(&monkey::net::connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void monkey::net::connection::handle_read_head( const boost::system::error_code& e, std::size_t bytes_transferred )
{
	if (!e && bytes_transferred != 0) {
		assert(bytes_transferred == sizeof(int));
		monkey::utils::memory_stream ms((unsigned char*)buffer_header_.c_array(), buffer_header_.size());
		int nextPackageLen = ms.ReadInt32();
		current_read_data_.reset(new package(nextPackageLen));
		start_read();
	}
	else if (bytes_transferred == 0) {
		cleanup();
	}
}

void monkey::net::connection::handle_read( const boost::system::error_code& e, std::size_t bytes_transferred )
{
	if (!e && bytes_transferred != 0) {
		assert(current_read_data_->size() == bytes_transferred);
		monkey::utils::memory_stream ms(*current_read_data_, current_read_data_->size());
		auto pMessage = ms.ReadProtobufMessage(bytes_transferred);
		if (pMessage)
			message_queue::get_instance()->push(shared_from_this(), pMessage);
		else {
			std::cout << "received unknow message type" << std::endl;
		}
		start_read_head();
	}
	else if (e == boost::asio::error::would_block){
		start_read();
	}
	else if (bytes_transferred == 0) {
		cleanup();
	}
}

void monkey::net::connection::handle_write( const boost::system::error_code& e, std::size_t bytes_transferred )
{
	boost::lock_guard<boost::mutex> lock(lock_);
	std::cout << "收到包长度:" << bytes_transferred << std::endl;
	std::cout << e.message() << std::endl;
	if (!e) {
		if (current_sent_data_->size() == bytes_transferred) {
			current_sent_data_.reset();
			if (!tobe_sent_data_.empty()) {
				current_sent_data_ = tobe_sent_data_.front();
				tobe_sent_data_.pop();
				start_write();
			}
		}
		else {
			start_write();
		}
	}
	else if (e == boost::asio::error::would_block) {
		start_write();
	}
}

boost::asio::ip::tcp::socket& monkey::net::connection::socket()
{
	return socket_;
}

void monkey::net::connection::start()
{
	start_read_head();
}

void monkey::net::connection::start_write()
{
	std::cout << "准备发送一个数据长度为: " << current_sent_data_->size() << "的包" << std::endl;
	boost::asio::async_write(socket_, boost::asio::buffer((unsigned char*)*current_sent_data_, current_sent_data_->size()),
		boost::bind(&connection::handle_write, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void monkey::net::connection::send_protobuf( boost::shared_ptr<const google::protobuf::Message> message )
{
	using namespace boost;
	//包的总长度是包内容长度+包头的4字节(一个int)长度
	boost::shared_ptr<package> pkg(new package(net_helper::get_protobuf_package_len(message.get()) + sizeof(int)));
	utils::memory_stream ms(*pkg, pkg->size());
	ms.WriteProtobufMessage(message.get());

	boost::lock_guard<boost::mutex> lock(lock_);

	if (current_sent_data_) {
		tobe_sent_data_.push(pkg);
	}
	else {
		current_sent_data_ = pkg;
		start_write();
	}
}

boost::shared_ptr<session> monkey::net::connection::get_session()
{
	if(session_.expired()) {
		return boost::shared_ptr<session>();
	}
	else {
		return session_.lock();
	}
}

void monkey::net::connection::close()
{
	socket_.close();
	cleanup();
	//TODO 应该还会做一个session池优化性能,在此处把session放入池内
}


connection::~connection( void )
{
	lock_.destroy();
}

void connection::handle_connected( const boost::system::error_code& e )
{
	if (!e) {
		start();
	}
}

void connection::cleanup()
{
	if (!session_.expired()) {
		session_manager::get_instance()->unregister_session_delay(session_key_);
	}
}

};
};