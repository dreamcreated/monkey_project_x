#include "scene_system.h"
#include <monkey/net/message_queue.h>
#include <monkey/net/session_manager.h>
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

void scene_system::on_user_enter( boost::shared_ptr<monkey::net::session> client_context )
{

}

void scene_system::on_user_leave( boost::shared_ptr<monkey::net::session> client_context )
{

}

void scene_system::on_scene_enter( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg )
{
	std::cout << "on_enter scene" << std::endl;
	msg->PrintDebugString();
	auto &sessions = session_manager::get_instance()->get_session_map();
	for(auto i = sessions.begin(); i != sessions.end(); ++i) {
		i->second->get_connection()->send_protobuf(msg);
	}
}

void scene_system::on_scene_move( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_move> msg )
{
	std::cout << "on_scene_move" << std::endl;
	msg->PrintDebugString();
	auto &sessions = session_manager::get_instance()->get_session_map();
	for(auto i = sessions.begin(); i != sessions.end(); ++i) {
		i->second->get_connection()->send_protobuf(msg);
	}
}
