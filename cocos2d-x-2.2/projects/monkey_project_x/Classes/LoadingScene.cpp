#include "LoadingScene.h"
#include "LoginScene.h"

USING_NS_CC;

bool LoadingScene::init()
{
	//TODO ��ʼ������Ϸ��Դ,����û����Դ���Լ��������ӳ�һ���ֱ�ӵ���loadingEnd
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