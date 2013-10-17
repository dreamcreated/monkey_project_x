#pragma once
#include "cocoa/CCObject.h"
#include <monkey/utils/singleton.hpp>
class messages_queue_wrapper 
	: public cocos2d::CCObject
	, public monkey::utils::singleton<messages_queue_wrapper>
{
public:
	messages_queue_wrapper(void);
	~messages_queue_wrapper(void);
	void update(float dt);
};

