#ifndef __PLAYERSPRITE_H__
#define __PLAYERSPRITE_H__
#include "cocos2d.h"
#include <common/messages/scene_messages.pb.h>

USING_NS_CC;

class PlayerSprite : public CCLayer {
public:
	enum {
		kWalkActionTag
	};
	bool init();
	CREATE_FUNC(PlayerSprite);

	CCMoveTo* GetMoveToAction(const CCPoint& target);
	CCMoveBy* GetMoveByActionByDistance( float distance, const CCPoint& target);
	CCMoveBy* GetMoveByActionByDistanceForMap( float distance, const CCPoint& target);
	float GetSpeed() const;
	int GetTagByPlayerID () const;
	static int GetTagByPlayerID(int playerid);
	void SetPlayerInfo( const ::common::player_info& info );
private:
	float m_speed;
	common::player_info m_player_info;
};

#endif