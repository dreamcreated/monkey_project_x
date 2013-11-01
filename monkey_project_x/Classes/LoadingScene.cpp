#include "LoadingScene.h"
#include "LoginScene.h"

USING_NS_CC;

bool LoadingScene::init()
{
	//TODO 开始加载游戏资源,现在没有资源可以加载所以延迟一秒后直接调用loadingEnd
	CCFiniteTimeAction *pDelayAction = CCDelayTime::create(1.0f);
	CCSequence *pSeqActions = CCSequence::create(pDelayAction, CCCallFunc::create(this, callfunc_selector(LoadingScene::loadingEnd)), NULL);
	this->runAction(pSeqActions);
	return true;
}

cocos2d::CCScene* LoadingScene::scene()
{
	auto pScene = cocos2d::CCScene::create();
	auto pLayer = LoadingScene::create();
	pScene->addChild(pLayer);
	return pScene;
}

void LoadingScene::loadingEnd()
{
	CCDirector::sharedDirector()->replaceScene(LoginScene::scene());
}