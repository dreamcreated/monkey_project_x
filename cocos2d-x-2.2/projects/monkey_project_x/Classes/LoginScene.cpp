#include "LoginScene.h"
#include "cocos-ext.h"
#include <common/messages/Login.pb.h>
#include <boost/shared_ptr.hpp>
#include "game_network.h"

USING_NS_CC;
USING_NS_CC_EXT;

LoginScene::LoginScene(void)
{
}


LoginScene::~LoginScene(void)
{
}

bool LoginScene::init()
{
	if (!CCLayer::init()) {
		return false;
	}

	UILayer* ui = UILayer::create();
	ui->setTag(LOGIN_UI_TAG);
	this->addChild(ui);
	auto pUI = CCUIHELPER->createWidgetFromJsonFile("UI/DemoLogin/DemoLogin.json");
	pUI->setTag(LOGIN_UI_WIDGET_TAG);
	ui->addWidget(pUI);
	auto pLoginBtn = dynamic_cast<UIButton*>(pUI->getChildByName("login_Button"));
	pLoginBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::loginRelease));
	auto pCloseBtn = dynamic_cast<UIButton*>(pUI->getChildByName("close_Button"));
	pCloseBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::closeGame));
	return true;
}

cocos2d::CCScene* LoginScene::scene()
{
	CCScene *scene = CCScene::create();
	LoginScene* layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}

void LoginScene::closeGame( CCObject* sender )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void LoginScene::loginRelease( CCObject* sender )
{
	auto pWidget = dynamic_cast<UIWidget*>(dynamic_cast<UIButton*>(sender)->getParent());
	auto pTBName = dynamic_cast<UITextField*>(pWidget->getChildByName("name_TextField"));
	auto pTBPassword = dynamic_cast<UITextField*>(pWidget->getChildByName("password_TextField"));
	boost::shared_ptr<common::Login> pMsgLogin(new common::Login);
	pMsgLogin->set_username(pTBName->getStringValue());
	pMsgLogin->set_password(pTBPassword->getStringValue());
	auto pConnection = game_network::get_instance()->create_connection("127.0.0.1", "1991");
	pConnection->set_tag(GAME_SESSION);
	game_network::get_instance()->send_message_after_connected_send(SESSIONS::GAME_SESSION, pMsgLogin);
}
