#include "MapLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MapLayer::SetMapID( int mapid )
{
	//TODO ���Ե���ͼID,ֻ����һ����ͼ
	CCNode* pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("RPGGame.json");
	this->addChild(pNode);
	return true;
}

bool MapLayer::init()
{
	return true;
}

