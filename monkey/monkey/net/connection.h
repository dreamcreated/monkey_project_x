#pragma once
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <queue>
#include <google/protobuf/message.h>
#include <boost/shared_array.hpp>
#include <boost/weak_ptr.hpp>
#include "package.h"
#include "session.h"
#include <boost/thread.hpp>

namespace monkey {
namespace net {

class session_factory_base;

class connection
	: public boost::enable_shared_from_this<connection>
	, private boost::noncopyable
{
	friend class session_factory_base;
public:
	explicit connection(boost::asio::io_service& io_service);
	virtual ~connection(void);
	boost::asio::ip::tcp::socket& socket();
	void start();
	void send_protobuf(boost::shared_ptr<const google::protobuf::Message> message);
	boost::shared_ptr<session> get_session();
	void close();
protected:
	virtual void handle_connected(const boost::system::error_code& e);
	virtual void handle_read(const boost::system::error_code& e,
		std::size_t bytes_transferred);
	virtual void handle_read_head(const boost::system::error_code& e,
		std::size_t bytes_transferred);

	virtual void handle_write(const boost::system::error_code& e,
		std::size_t bytes_transferred);

private:
	void start_write();

	void start_read_head();
	void start_read();

	boost::asio::ip::tcp::socket socket_;

	boost::array<char, sizeof(int)> buffer_header_;

	//////////////////////////////////////////////////////////////////////////
	//发送相关
	//////////////////////////////////////////////////////////////////////////

	//队列中待发送的数据
	std::queue<boost::shared_ptr<package>> tobe_sent_data_;
	//当前正在发送的数据
	boost::shared_ptr<package> current_sent_data_;

	//////////////////////////////////////////////////////////////////////////
	//接收相关
	//////////////////////////////////////////////////////////////////////////
	boost::shared_ptr<package> current_read_data_;
	std::size_t current_read_bytes_;
	int package_len_;

	boost::weak_ptr<session> session_;
	std::string session_key_;
	boost::mutex lock_;

	void cleanup();
};

typedef boost::shared_ptr<connection> connection_ptr;

}
}

