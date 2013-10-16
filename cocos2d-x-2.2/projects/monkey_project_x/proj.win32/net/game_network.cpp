#include "game_network.h"
#include <common/messages/Login.pb.h>
#include <common/messages/scene_messages.pb.h>


game_network::game_network(void)
{
}


game_network::~game_network(void)
{
}

void game_network::on_connected( boost::shared_ptr<connection_client> connection )
{
	if (connection->tag() == LOGIN_SESSION) {
		boost::shared_ptr<common::Login> login(new common::Login);
		login->set_username("lida");
		login->set_password("1");
		connection->send_protobuf(login);
		boost::shared_ptr<common::scene_enter> scene_enter(new common::scene_enter);
		scene_enter->set_last_scene_id(100);
		connection->send_protobuf(scene_enter);
		boost::shared_ptr<common::scene_move> scene_move(new common::scene_move);
		scene_move->set_target_x(1);
		scene_move->set_target_y(2);
		scene_move->set_target_z(3);
		connection->send_protobuf(scene_move);
	}
	else  {

	}
}
