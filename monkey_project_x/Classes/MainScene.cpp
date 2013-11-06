#include "MainScene.h"

USING_NS_CC;

bool MainScene::init()
{
	return true;
}

bool MainScene::ChangeMap( int mapid )
{
	auto oldMapLayer = GetMapLayer();
	if (oldMapLayer) {
		this->removeChild(oldMapLayer);
		oldMapLayer->release();
	}
	oldMapLayer = MapLayer::create();
	oldMapLayer->SetMapID(mapid);
	oldMapLayer->setTag(kMapLayerTag);
	this->addChild(oldMapLayer);
	return true;
}

MainScene::MainScene()
{

}

MapLayer* MainScene::GetMapLayer()
{
	return dynamic_cast<MapLayer*>(this->getChildByTag(kMapLayerTag));
}
