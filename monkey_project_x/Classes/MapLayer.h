#ifndef __MAPLAYER_H__
#define __MAPLAYER_H__
#include "cocos2d.h"
#include "PlayerSprite.h"

class MapLayer : public cocos2d::CCLayer {
public:
	virtual bool init();
	bool SetMapID(int mapid);
	CREATE_FUNC(MapLayer);
	int GetMapWidth();
	int GetMapHeight();
	CCNode* GetMapLayer();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);	PlayerSprite* GetHeroSprite();
private:
	enum {
		kMapLayerTag,
		kMyHeroTag,
		kReverseToCenterPointActionTag
	};
};

#endif