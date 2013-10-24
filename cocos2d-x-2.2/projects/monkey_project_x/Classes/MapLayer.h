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
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);	PlayerSprite* GetHeroSprite();	void heroMoveComplete(CCObject* pTouch);	void allMoveComplete();	virtual void draw(); 
// 	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
// 	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
private:
	enum {
		kMapLayerTag,
		kMyHeroTag,
		kReverseToCenterPointActionTag
	};
	CCRect m_heroMoveRect;
};

#endif