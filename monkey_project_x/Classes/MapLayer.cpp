#include "MapLayer.h"
#include "cocos-ext.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <common/messages/scene_messages.pb.h>
#include "ClientUserData.h"
#include "game_network.h"
#include "scene_system.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MapLayer::SetMapID( int mapid )
{
	//TODO 忽略掉地图ID,只载入一个地图
	CCNode* pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("RPGGame.json");
	pNode->setZOrder(-100);
	pNode->setTag(kMapLayerTag);
	pNode->setScale(2.0f);
	this->addChild(pNode);
	auto designSize = CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize();
	auto halfScreenSize = CCSizeMake(designSize.width / 2, designSize.height / 2);
	this->setPosition(halfScreenSize - GetHeroSprite()->getPosition());
	return true;
}

bool MapLayer::init()
{
	auto pHero = PlayerSprite::create();
	pHero->setTag(kMyHeroTag);
	this->addChild(pHero, 10);
	pHero->setPosition(ccp(0, 0));
	pHero->setScale(0.3f);
	//this->setTouchEnabled(true);
	auto pTouchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pTouchDispatcher->addTargetedDelegate(this, 0, true);
	auto pDirector = CCDirector::sharedDirector();
	auto designSize = pDirector->getOpenGLView()->getDesignResolutionSize();
	pHero->setPosition(GetMapWidth() / 2, GetMapHeight() / 2);

	ReloadPlayers();
	return true;
}

int MapLayer::GetMapWidth()
{
	return 1024 * 2;
}

int MapLayer::GetMapHeight()
{
	return 768 * 2;
}

// void MapLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesBegan(pTouches, pEvent);
// }
// 
// void MapLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesMoved(pTouches, pEvent);
// }
// 
// void MapLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesEnded(pTouches, pEvent);
// }
// 
// void MapLayer::ccTouchesCancelled( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesCancelled(pTouches, pEvent);
// }

bool MapLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void MapLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchMoved(pTouch, pEvent);
}

void MapLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchEnded(pTouch, pEvent);

	auto pHero = GetHeroSprite();

	pHero->stopActionByTag(PlayerSprite::kWalkActionTag);
	pHero->stopActionByTag(kReverseToCenterPointActionTag);
	auto des = this->convertTouchToNodeSpace(pTouch);
	HeroGotoDes(des);
}

void MapLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchCancelled(pTouch, pEvent);
}

CCNode* MapLayer::GetMapLayer()
{
	auto mapLayer = this->getChildByTag(kMapLayerTag);
	return mapLayer;
}

PlayerSprite* MapLayer::GetHeroSprite()
{
	auto pHeroSprite = this->getChildByTag(kMyHeroTag);
	return dynamic_cast<PlayerSprite*>(pHeroSprite);
}

void MapLayer::HeroGotoDes( const CCPoint& des )
{
	auto pHero = GetHeroSprite();
	auto pMoveTo = pHero->GetMoveToAction(des);
	pMoveTo->setTag(PlayerSprite::kWalkActionTag);
	pHero->runAction(pMoveTo);
	auto pFollow = CCFollow::create(pHero, CCRect(0, 0, GetMapWidth(), GetMapHeight()));
	this->runAction(pFollow);

	boost::shared_ptr<common::scene_move> pSceneMove(new common::scene_move);// = boost::make_shared<common::scene_move>();
	pSceneMove->set_player_id(ClientUserData::get_instance()->Player_id());
	pSceneMove->set_target_x(des.x);
	pSceneMove->set_target_y(des.y);
	game_network::get_instance()->send_message(SESSIONS::GAME_SESSION, pSceneMove);
}

void MapLayer::GotoDesForSpecifiedPlayerID( int player_id, const CCPoint& des )
{
	auto pPlayerSprite = dynamic_cast<PlayerSprite*>(this->getChildByTag(PlayerSprite::GetTagByPlayerID(player_id)));
	CCAssert(pPlayerSprite, "player_id not found in this maplayer");
	_SpriteGotoDes(pPlayerSprite, des);
}

void MapLayer::_SpriteGotoDes( PlayerSprite* sprite, const CCPoint& des )
{
	sprite->stopActionByTag(PlayerSprite::kWalkActionTag);
	auto pMoveTo = sprite->GetMoveToAction(des);
	pMoveTo->setTag(PlayerSprite::kWalkActionTag);
	sprite->runAction(pMoveTo);
}

void MapLayer::ReloadPlayers()
{
	ClearPlayers();

	//TODO 缺少一个是否在当前显示范围内的判断(当前屏幕在地图的RECT和每个角色判断相交,相交就加进去显示不相交就不管)

	auto &players = scene_system::get_instance()->get_players();
	for(auto i = players.begin(); i != players.end(); ++i) {
		auto pPlayerSprite = PlayerSprite::create();
		pPlayerSprite->SetPlayerInfo(*(i->second));
		pPlayerSprite->setScale(0.3f);
		this->addChild(pPlayerSprite);
	}
}

void MapLayer::ClearPlayers()
{
	auto children = this->getChildren();
	for(unsigned int i = 0; i < children->count();) {
		auto player = children->objectAtIndex(i);
		auto spritePlayer = dynamic_cast<PlayerSprite*>(player);
		if (spritePlayer && spritePlayer->getTag() != kMyHeroTag) {
			children->removeObjectAtIndex(i);
		}
		else {
			++i;
		}
	}
}
