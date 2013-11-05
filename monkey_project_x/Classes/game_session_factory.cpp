#include "game_session_factory.h"
#include <common/messages/Login.pb.h>
#include "game_network.h"
#include <boost/lexical_cast.hpp>
#include "ClientUserData.h"


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
		if (p_login_return->login_successed()) {
			ClientUserData::get_instance()->Player_id(p_login_return->player_id());
			boost::shared_ptr<common::scene_enter> pSceneEnter(new common::scene_enter);
			pSceneEnter->set_scene_id(1);
			conn->send_protobuf(pSceneEnter);
		}
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
	game_network::get_instance()->register_session(SESSIONS::GAME_SESSION, pSession);
	return SESSIONS::GAME_SESSION;
}

boost::shared_ptr<monkey::net::session> game_session_factory::new_session( boost::shared_ptr<google::protobuf::Message> message ) const
{
	return boost::shared_ptr<monkey::net::session>(new monkey::net::session);
}
