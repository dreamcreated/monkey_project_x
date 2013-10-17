#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "messages_queue_wrapper.h"
#include "game_network.h"
#include "LoadingScene.h"
#include "game_session_factory.h"
#include <boost/shared_ptr.hpp>
#include <monkey/net/message_queue.h>

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	//注册消息分发事件
	pDirector->getScheduler()->scheduleUpdateForTarget(messages_queue_wrapper::get_instance().get(), 0, false);

	boost::shared_ptr<game_session_factory> pFac(new game_session_factory);
	monkey::net::message_queue::get_instance()->register_session_factory(pFac);

	game_network::get_instance()->async_start_without_message_queue();


    // run
    pDirector->runWithScene(LoadingScene::scene());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
