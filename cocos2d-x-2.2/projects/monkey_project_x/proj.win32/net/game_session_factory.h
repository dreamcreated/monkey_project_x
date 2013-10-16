#pragma once
#include <monkey/net/session_factory_base.h>
//��Ϸ��������session factory
class game_session_factory : public monkey::net::session_factory_base
{
public:
	game_session_factory(void);
	virtual ~game_session_factory(void);


	virtual bool verify_connection(boost::shared_ptr<monkey::net::connection> conn, boost::shared_ptr<google::protobuf::Message> message) const;
	virtual void on_verify_failed(boost::shared_ptr<google::protobuf::Message> message) const;
	//����session��key
	virtual std::string on_verify_successed(boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<google::protobuf::Message> message) const;
	virtual boost::shared_ptr<monkey::net::session> new_session(boost::shared_ptr<google::protobuf::Message> message) const;
};

