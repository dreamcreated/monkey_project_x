#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__
#include "cocos2d.h"
class LoadingScene : public cocos2d::CCLayer {
public:
	bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(LoadingScene);

	void loadingEnd();

};
#endif
