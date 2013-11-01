#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#include "cocos2d.h"
#include "MapLayer.h"

class MainScene : public cocos2d::CCScene {
public:
	MainScene();
	bool init();
	bool ChangeMap(int mapid);
	CREATE_FUNC(MainScene);
private:
	MapLayer* m_map_layer;
};


#endif