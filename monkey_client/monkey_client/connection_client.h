#pragma once
#include <monkey/net/connection.h>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
class network;
class connection_client 
	: public monkey::net::connection
{
public:
	void handle_connected(const boost::system::error_code& e);

	explicit connection_client(boost::asio::io_service& io_service, boost::shared_ptr<network> network)
		: monkey::net::connection(io_service)
		, network_(network) {}

	virtual ~connection_client(void);

	int tag() const { return tag_; }
	void set_tag(int val) { tag_ = val; }
private:
	boost::weak_ptr<network> network_;
	int tag_;
};
typedef boost::shared_ptr<connection_client> connection_client_ptr;

