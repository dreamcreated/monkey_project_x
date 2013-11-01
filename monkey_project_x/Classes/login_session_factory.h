#pragma once
#include <monkey/net/session_factory_base.h>
//µÇÂ½·þÎñÆ÷µÄsession factory
class login_session_factory : public monkey::net::session_factory_base
{
public:
	login_session_factory(void);
	virtual ~login_session_factory(void);

	virtual bool verify_connection(boost::shared_ptr<monkey::net::connection> conn, boost::shared_ptr<google::protobuf::Message> message) const = 0;
	virtual void on_verify_failed(boost::shared_ptr<google::protobuf::Message> message) const = 0;
	virtual std::string on_verify_successed(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<google::protobuf::Message> message) const = 0;
	virtual boost::shared_ptr<monkey::net::session> new_session(boost::shared_ptr<google::protobuf::Message> message) const = 0;
};

