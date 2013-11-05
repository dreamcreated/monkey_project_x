#include "MainScene.h"

USING_NS_CC;

bool MainScene::init()
{
	return true;
}

bool MainScene::ChangeMap( int mapid )
{
	if (m_map_layer) {
		this->removeChild(m_map_layer);
		m_map_layer->release();
	}
	m_map_layer = MapLayer::create();
	m_map_layer->SetMapID(mapid);
	m_map_layer->setTag(kMapLayerTag);
	this->addChild(m_map_layer);
	return true;
}

MainScene::MainScene()
	: m_map_layer(NULL)
{

}

MapLayer* MainScene::GetMapLayer()
{
	return dynamic_cast<MapLayer*>(this->getChildByTag(kMapLayerTag));
}
