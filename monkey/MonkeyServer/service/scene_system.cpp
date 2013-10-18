#include "scene_system.h"
#include <monkey/net/message_queue.h>
#include <monkey/net/session_manager.h>
#include "client_context.h"

using namespace monkey::net;


scene_system::scene_system(void)
	: system_service("scene_system")
{
}


scene_system::~scene_system(void)
{
}

bool scene_system::init()
{
	 auto &message_dispatcher = message_queue::get_instance()->get_dispatcher();
	 message_dispatcher.register_message_callback<common::scene_enter>(&scene_system::on_scene_enter);
	 message_dispatcher.register_message_callback<common::scene_move>(&scene_system::on_scene_move);
	 return true;
}

void scene_system::fint()
{

}

void scene_system::on_user_enter( boost::shared_ptr<monkey::net::session> pSession )
{
}

void scene_system::on_user_leave( boost::shared_ptr<monkey::net::session> pSession )
{

}

void scene_system::on_scene_enter( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg )
{
	std::cout << "on_enter scene" << std::endl;
	msg->PrintDebugString();
	auto pClientContext = boost::dynamic_pointer_cast<client_context>(pSession);
	pClientContext->User_data().Scene_id(msg->scene_id());

	//广播给所有玩家
	auto &sessions = session_manager::get_instance()->get_session_map();
	for(auto i = sessions.begin(); i != sessions.end(); ++i) {
		i->second->get_connection()->send_protobuf(msg);
	}
}

void scene_system::on_scene_move( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_move> msg )
{
	std::cout << "on_scene_move" << std::endl;
	msg->PrintDebugString();
	auto pClientContext = boost::dynamic_pointer_cast<client_context>(pSession);
	pClientContext->User_data().Pos_x(msg->target_x());
	pClientContext->User_data().Pos_y(msg->target_y());
	auto &sessions = session_manager::get_instance()->get_session_map();
	for(auto i = sessions.begin(); i != sessions.end(); ++i) {
		i->second->get_connection()->send_protobuf(msg);
	}
}
