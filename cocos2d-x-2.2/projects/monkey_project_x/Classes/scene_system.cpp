#include "scene_system.h"
#include <monkey/net/message_queue.h>
#include "ClientUserData.h"
#include "MainScene.h"
#include "cocos2d.h"

USING_NS_CC;

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
	message_dispatcher.register_message_callback<common::scene_move>(&scene_system::on_scene_move);
	return true;
}

void scene_system::on_scene_enter( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg )
{
	if (msg->player_id() == ClientUserData::get_instance()->Player_id()) {
		MainScene *mainScene = MainScene::create();
		mainScene->ChangeMap(1);
		CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.0f, mainScene));
	}
	else {
		//TODO 其他玩家进入
	}
}

void scene_system::on_scene_move( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_move> msg )
{
	if (msg->player_id() != ClientUserData::get_instance()->Player_id()) {
		//TODO 处理其他人的移动
	}
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
