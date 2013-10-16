#include "session_factory.h"
#include <iostream>
#include "../service/client_context.h"
#include <common/messages/Login.pb.h>
#include <boost/lexical_cast.hpp>


session_factory::session_factory(void)
{
}


session_factory::~session_factory(void)
{
}

bool session_factory::verify_connection( boost::shared_ptr<monkey::net::connection> conn, boost::shared_ptr<google::protobuf::Message> message ) const
{
	auto pLogin = boost::dynamic_pointer_cast<common::Login>(message);
	std::cout << "User Login:" <<std::endl;
	if (pLogin) {
		pLogin->PrintDebugString();
		boost::shared_ptr<common::LoginReturn> p_login_return(new common::LoginReturn);
		if (pLogin->password() == "1") {
			p_login_return->set_login_successed(true);
			conn->send_protobuf(p_login_return);
			return true;
		}
		p_login_return->set_login_successed(false);
		conn->send_protobuf(p_login_return);
	}
	return false;
}

std::string session_factory::on_verify_successed( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<google::protobuf::Message> message ) const
{
	auto pClientContext = boost::dynamic_pointer_cast<client_context>(pSession);
	if (pClientContext) {
		//TODO 查询数据库,读取玩家资料写入pClientContext
	}
	else {
		assert(false);
	}
	static int session_id = 0;
	return boost::lexical_cast<std::string>(session_id++);
}

void session_factory::on_verify_failed( boost::shared_ptr<google::protobuf::Message> message ) const
{
	std::cout << message->GetTypeName() << "verify failed" << std::endl;
	message->PrintDebugString();
}

boost::shared_ptr<monkey::net::session> session_factory::new_session( boost::shared_ptr<google::protobuf::Message> message ) const
{
	return boost::shared_ptr<monkey::net::session>(new client_context());
}
