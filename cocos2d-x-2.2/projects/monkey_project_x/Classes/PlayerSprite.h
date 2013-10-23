#ifndef __PLAYERSPRITE_H__
#define __PLAYERSPRITE_H__
#include "cocos2d.h"

USING_NS_CC;

class PlayerSprite : public CCLayer {
public:
	enum {
		kWalkActionTag
	};
	bool init();
	CREATE_FUNC(PlayerSprite);
	CCMoveTo* GetMoveToActionByDistance( float distance, const CCPoint& target);
	CCMoveBy* GetMoveByActionByDistance( float distance, const CCPoint& target);
	CCMoveBy* GetMoveByActionByDistanceForMap( float distance, const CCPoint& target);
private:
	float m_speed;
};

#endif