#include "network.h"
#include <monkey/net/message_queue.h>
using namespace monkey::net;

network::network(void)
{
	io_service_.reset(new boost::asio::io_service());
	work_.reset(new boost::asio::io_service::work(*io_service_));
}


network::~network(void)
{
}

connection_client_ptr network::create_connection( const std::string& server_ip, const std::string& server_port )
{
	connection_client_ptr p_connection(new connection_client(*io_service_, shared_from_this()));
	boost::asio::ip::tcp::resolver resolver(*io_service_);
	boost::asio::ip::tcp::resolver::query query(server_ip, server_port);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	p_connection->socket().async_connect(endpoint,
		boost::bind(&connection_client::handle_connected, p_connection
		, boost::asio::placeholders::error));
	return p_connection;
}

void network::send_message( const std::string& session_name, boost::shared_ptr<google::protobuf::Message> message )
{
	sessions_map_.at(session_name)->get_connection()->send_protobuf(message);
}

void network::async_start_without_message_queue()
{
	thread_.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, io_service_)));
}

void network::async_start_service()
{
	message_queue::get_instance()->async_run();
	thread_.reset(new boost::thread(boost::bind(&boost::asio::io_service::run, io_service_)));
}

void network::sync_start_service()
{
	message_queue::get_instance()->async_run();
	io_service_->run();
}

void network::join()
{
	io_service_->stop();
	if (thread_)
		thread_->join();
	message_queue::get_instance()->async_stop();
}

bool network::register_session( const std::string& session_name, boost::shared_ptr<monkey::net::session> session )
{
	auto ret = sessions_map_.insert(std::make_pair(session_name, session));
	return ret.second;
}


