#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#include "cocos2d.h"
#include "MapLayer.h"

USING_NS_CC;

class MainScene : public cocos2d::CCScene {
public:
	MainScene();
	bool init();
	bool ChangeMap(int mapid);
	CREATE_FUNC(MainScene);
	MapLayer* GetMapLayer();
private:
	MapLayer* m_map_layer;

	enum {
		kMapLayerTag
	};
};


#endif