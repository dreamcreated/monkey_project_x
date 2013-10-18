#ifndef __MAPLAYER_H__
#define __MAPLAYER_H__
#include "cocos2d.h"

class MapLayer : public cocos2d::CCLayer {
public:
	bool init();
	bool SetMapID(int mapid);
	CREATE_FUNC(MapLayer);
};

#endif