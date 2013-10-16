#pragma once
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "connection.h"
#include "io_service_pool.h"
namespace monkey {
namespace net{

class server
	: private boost::noncopyable
{
public:
	explicit server(const std::string& address, const std::string& port,
		std::size_t io_service_pool_size);

	void run();

private:
	void start_accept();
	void handle_accept(const boost::system::error_code& e);
	void handle_stop();

	io_service_pool io_service_pool_;
	boost::asio::signal_set signals_;
	boost::asio::ip::tcp::acceptor acceptor_;
	connection_ptr new_connection_;
};

};
};