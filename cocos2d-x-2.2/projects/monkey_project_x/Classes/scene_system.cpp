#include "scene_system.h"
#include <monkey/net/message_queue.h>

using namespace monkey::net;

scene_system::scene_system(void)
	: system_service("SCENE_SYSTEM")
{
}


scene_system::~scene_system(void)
{
}

bool scene_system::init()
{
	auto &message_dispatcher = message_queue::get_instance()->get_dispatcher();
	//注册消息处理函数
	message_dispatcher.register_message_callback<common::scene_enter>(&scene_system::on_scene_enter);
	return true;
}

void scene_system::on_scene_enter( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg )
{
	//处理scene_enter消息
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
