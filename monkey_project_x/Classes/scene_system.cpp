#include "scene_system.h"
#include <monkey/net/message_queue.h>
#include "ClientUserData.h"
#include "MainScene.h"
#include "cocos2d.h"
#include "PlayerSprite.h"

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
	message_dispatcher.register_message_callback<common::player_list>(&scene_system::on_player_list);
	return true;
}

void scene_system::on_scene_enter( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_enter> msg )
{
	if (msg->player_info().player_id() == ClientUserData::get_instance()->Player_id()) {
		MainScene *mainScene = MainScene::create();
		mainScene->ChangeMap(1);
		CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.0f, mainScene));
	}
	else {
		auto pPlayer = PlayerSprite::create();
		pPlayer->SetPlayerInfo(msg->player_info());
		auto pMainScene = dynamic_cast<MainScene*>(CCDirector::sharedDirector()->getRunningScene());
		if(pMainScene) {
			pMainScene->GetMapLayer()->addChild(pPlayer);
		}
		else {

		}
	}
}

void scene_system::on_scene_move( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::scene_move> msg )
{
	if (msg->player_id() != ClientUserData::get_instance()->Player_id()) {
		auto pMainScene = dynamic_cast<MainScene*>(CCDirector::sharedDirector()->getRunningScene());
		if (!pMainScene)
			return;
		auto pMapLayer = dynamic_cast<MapLayer*>(pMainScene->GetMapLayer());
		assert(pMapLayer);
		pMapLayer->GotoDesForSpecifiedPlayerID(msg->player_id(), ccp(msg->target_x(), msg->target_y()));
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

void scene_system::on_player_list( boost::shared_ptr<monkey::net::session> pSession, boost::shared_ptr<common::player_list> msg )
{
	auto pMainScene = dynamic_cast<MainScene*>(CCDirector::sharedDirector()->getRunningScene());
	if(pMainScene) {
		auto pMapLayer = pMainScene->GetMapLayer();
		for(auto i = 0; i < msg->players_size(); ++i) {
			auto& playerInfo = msg->players(i);
			if (pMapLayer) {
				auto pCurrentSprite = dynamic_cast<PlayerSprite*>(pMapLayer->getChildByTag(PlayerSprite::GetTagByPlayerID(playerInfo.player_id())));
				if (pCurrentSprite) {
					pCurrentSprite->SetPlayerInfo(playerInfo);
				}
				else {
					auto pPlayerSprite = PlayerSprite::create();
					pPlayerSprite->SetPlayerInfo(playerInfo);
					pMapLayer->addChild(pPlayerSprite);
				}
			}
		}
	}
}
