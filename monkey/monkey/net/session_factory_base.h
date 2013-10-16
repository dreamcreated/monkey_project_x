#pragma once
#include <google/protobuf/message.h>
#include <boost/shared_ptr.hpp>
#include "connection.h"
#include "session.h"
#include <string>
namespace monkey{
namespace net{

class session_factory_base
{
public:
	session_factory_base();
	virtual ~session_factory_base();

	virtual bool verify_connection(boost::shared_ptr<connection> conn, boost::shared_ptr<google::protobuf::Message> message) const = 0;
	virtual void on_verify_failed(boost::shared_ptr<google::protobuf::Message> message) const = 0;
	//·µ»ØsessionµÄkey
	virtual std::string on_verify_successed(boost::shared_ptr<session> pSession, boost::shared_ptr<google::protobuf::Message> message) const = 0;
	virtual boost::shared_ptr<session> new_session(boost::shared_ptr<google::protobuf::Message> message) const = 0;

	boost::shared_ptr<session> create_session(boost::shared_ptr<connection> conn, boost::shared_ptr<google::protobuf::Message> message);
};

};
};