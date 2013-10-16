#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <map>
#include <string>
#include <monkey/net/session.h>
#include <google/protobuf/message.h>
#include "connection_client.h"
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

class network 
	: public boost::enable_shared_from_this<network>
	, private boost::noncopyable
{
public:
	network(void);
	~network(void);
	bool register_session(const std::string& session_name, boost::shared_ptr<monkey::net::session> session);
	connection_client_ptr create_connection(const std::string& server_ip, const std::string& server_port);
	void send_message(const std::string& session_name, boost::shared_ptr<google::protobuf::Message> message);
	void async_start_service();
	void sync_start_service();
	void join();
	virtual void on_connected( boost::shared_ptr<connection_client> connection) = 0;
private:
	std::map<std::string, boost::shared_ptr<monkey::net::session>> sessions_map_;
	boost::shared_ptr<boost::thread> thread_;
	boost::shared_ptr<boost::asio::io_service > io_service_;
};

