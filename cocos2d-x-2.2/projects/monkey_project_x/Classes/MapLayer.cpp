#include "MapLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MapLayer::SetMapID( int mapid )
{
	//TODO 忽略掉地图ID,只载入一个地图
	CCNode* pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("RPGGame.json");
	this->addChild(pNode);
	return true;
}

bool MapLayer::init()
{
	return true;
}

