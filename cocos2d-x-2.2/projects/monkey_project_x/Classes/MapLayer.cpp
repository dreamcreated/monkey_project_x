#include "MapLayer.h"
#include "cocos-ext.h"

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
	auto distance = pHero->getPosition().getDistance(pTouch->getLocation());
	auto pMoveTo = pHero->GetMoveToAction(this->convertTouchToNodeSpace(pTouch));
	pMoveTo->setTag(PlayerSprite::kWalkActionTag);
	pHero->runAction(pMoveTo);
	auto pFollow = CCFollow::create(pHero, CCRect(0, 0, GetMapWidth(), GetMapHeight()));
	this->runAction(pFollow);

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