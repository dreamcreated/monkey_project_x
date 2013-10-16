#include "server.h"
#include <boost/bind.hpp>
#include "message_queue.h"

void monkey::net::server::run()
{
	message_queue::get_instance()->async_run();
	io_service_pool_.run();
	message_queue::get_instance()->async_stop();
}

monkey::net::server::server( const std::string& address, const std::string& port, std::size_t io_service_pool_size )
	: io_service_pool_(io_service_pool_size)
	, signals_(io_service_pool_.get_io_service())
	, acceptor_(io_service_pool_.get_io_service())
	, new_connection_()
{
	signals_.add(SIGINT);
	signals_.add(SIGTERM);
#if defined(SIGQUIT)
	signals_.add(SIGQUIT);
#endif 
	signals_.async_wait(boost::bind(&server::handle_stop, this));

	boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
	boost::asio::ip::tcp::resolver::query query(address, port);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	start_accept();
}

void monkey::net::server::start_accept()
{
	new_connection_.reset(new connection(
		io_service_pool_.get_io_service()));
	acceptor_.async_accept(new_connection_->socket(),
		boost::bind(&server::handle_accept, this,
		boost::asio::placeholders::error));
}

void monkey::net::server::handle_accept( const boost::system::error_code& e )
{
	if (!e) {
		new_connection_->start();
	}

	start_accept();
}

void monkey::net::server::handle_stop()
{
	io_service_pool_.stop();
}
