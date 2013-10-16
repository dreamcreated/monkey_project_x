#include "game_session_factory.h"
#include <common/messages/Login.pb.h>
#include "game_network.h"
#include <boost/lexical_cast.hpp>


game_session_factory::game_session_factory(void)
{
}


game_session_factory::~game_session_factory(void)
{
}

bool game_session_factory::verify_connection( boost::shared_ptr<monkey::net::connection> conn, boost::shared_ptr<google::protobuf::Message> message ) const
{
	auto p_login_return = boost::dynamic_pointer_cast<common::LoginReturn>(message);
	if (p_login_return) {
		return p_login_return->login_successed();
	}
	return false;
}

void game_session_factory::on_verify_failed( boost::shared_ptr<google::protobuf::Message> message ) const
{
	std::cout << "Login failed" << std::endl;
}

std::string game_session_factory::on_verify_successed( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<google::protobuf::Message> message ) const
{
	return boost::lexical_cast<std::string>(SESSION_TYPE::GAME_SESSION);
}

boost::shared_ptr<monkey::net::session> game_session_factory::new_session( boost::shared_ptr<google::protobuf::Message> message ) const
{
	return boost::shared_ptr<monkey::net::session>(new monkey::net::session);
}
