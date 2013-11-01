#pragma once
#include "cocos2d.h"
class LoginScene : public cocos2d::CCLayer
{
	enum { 
		LOGIN_UI_TAG = 1,
		LOGIN_UI_WIDGET_TAG = 2,
	};
public:
	LoginScene(void);
	~LoginScene(void);

	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(LoginScene);

	void closeGame(CCObject* sender);
	void loginRelease(CCObject* sender);
};

