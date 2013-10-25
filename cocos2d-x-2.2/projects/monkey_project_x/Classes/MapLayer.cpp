#include "MapLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MapLayer::SetMapID( int mapid )
{
	//TODO ���Ե���ͼID,ֻ����һ����ͼ
	CCNode* pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("RPGGame.json");
	pNode->setZOrder(-100);
	pNode->setTag(kMapLayerTag);
	this->addChild(pNode);
	return true;
}

bool MapLayer::init()
{
	auto pHero = PlayerSprite::create();
	pHero->setTag(kMyHeroTag);
	this->addChild(pHero, 10);
	pHero->setPosition(ccp(0, 0));
	pHero->setScale(0.3f);
	//this->setTouchEnabled(true);
	auto pTouchDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pTouchDispatcher->addTargetedDelegate(this, 0, true);
	auto pDirector = CCDirector::sharedDirector();
	auto designSize = pDirector->getOpenGLView()->getDesignResolutionSize();
	const float heroRectWidth = 300;
	const float heroRectHeight = heroRectWidth / designSize.width * designSize.height;
	m_heroMoveRect.setRect((designSize.width - heroRectWidth) / 2, (designSize.height - heroRectHeight) / 2 , heroRectWidth, heroRectHeight);
	pHero->setPosition(m_heroMoveRect.getMidX(), m_heroMoveRect.getMidY());
	return true;
}

int MapLayer::GetMapWidth()
{
	return 1024;
}

int MapLayer::GetMapHeight()
{
	return 768;
}

// void MapLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesBegan(pTouches, pEvent);
// }
// 
// void MapLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesMoved(pTouches, pEvent);
// }
// 
// void MapLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesEnded(pTouches, pEvent);
// }
// 
// void MapLayer::ccTouchesCancelled( CCSet *pTouches, CCEvent *pEvent )
// {
// 	CCLayer::ccTouchesCancelled(pTouches, pEvent);
// }

bool MapLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void MapLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchMoved(pTouch, pEvent);
}

void MapLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchEnded(pTouch, pEvent);

	auto pHero = GetHeroSprite();
	auto pDirector = CCDirector::sharedDirector();
	auto designSize = pDirector->getOpenGLView()->getDesignResolutionSize();
	pHero->stopActionByTag(PlayerSprite::kWalkActionTag);
	pHero->stopActionByTag(kReverseToCenterPointActionTag);
	GetMapLayer()->stopActionByTag(PlayerSprite::kWalkActionTag);
	GetMapLayer()->stopActionByTag(kReverseToCenterPointActionTag);

// 	CCPoint leftTopPoint = ccp(m_heroMoveRect.getMinX(), m_heroMoveRect.getMaxY());
// 	CCPoint rightTopPoint = ccp(m_heroMoveRect.getMaxX(), m_heroMoveRect.getMaxY());
// 	CCPoint leftBottomPoint = ccp(m_heroMoveRect.getMinX(), m_heroMoveRect.getMinY());
// 	CCPoint rightBottomPoint = ccp(m_heroMoveRect.getMaxX(), m_heroMoveRect.getMinY());

	CCPoint line1Point1 = ccp(0, m_heroMoveRect.getMinY()); //�·����߶�
	CCPoint line1Point2 = ccp(designSize.width, m_heroMoveRect.getMinY());	//�·����߶�
	CCPoint line2Point1 = ccp(0, m_heroMoveRect.getMaxY());			//�Ϸ����߶�
	CCPoint line2Point2 = ccp(designSize.width, m_heroMoveRect.getMaxY());	//�Ϸ����߶�
	CCPoint line3Point1 = ccp(m_heroMoveRect.getMinX(), 0);			//���߶�
	CCPoint line3Point2 = ccp(m_heroMoveRect.getMinX(), designSize.height);	//���߶�
	CCPoint line4Point1 = ccp(m_heroMoveRect.getMaxX(), 0);				//�ҷ��߶�
	CCPoint line4Point2 = ccp(m_heroMoveRect.getMaxX(), designSize.height);		//�ҷ��߶�


	bool isIntersect = false;
	CCPoint intersectPoint;
	CCPoint heroPosition = pHero->getPosition();
	CCPoint targetPosition = pTouch->getLocation();
	
	if (pHero->getPosition().y > line1Point1.y) {
		if (ccpSegmentIntersect(line1Point1, line1Point2
			, heroPosition, targetPosition)) {
				intersectPoint = ccpIntersectPoint(line1Point1, line1Point2
					, heroPosition, targetPosition);
				isIntersect = true;
				intersectPoint.y += 5;
		}
	}
	if (pHero->getPosition().y <= line2Point1.y) {
		if (ccpSegmentIntersect(line2Point1, line2Point2
			, heroPosition, targetPosition)) {
				auto p = ccpIntersectPoint(line2Point1, line2Point2
					, heroPosition, targetPosition);
				if ((intersectPoint.x == CCPointZero.x && intersectPoint.y == CCPointZero.y) 
					|| (pHero->getPosition().getDistance(p) < pHero->getPosition().getDistance(intersectPoint))) {
						intersectPoint = p;
				}
				isIntersect = true;
				intersectPoint.y -= 5;
		}
	}
	if (pHero->getPosition().x >= line3Point1.x) {
		if (ccpSegmentIntersect(line3Point1, line3Point2
			, heroPosition, targetPosition)) {
				auto p = ccpIntersectPoint(line3Point1, line3Point2
					, heroPosition, targetPosition);
				if ((intersectPoint.x == CCPointZero.x && intersectPoint.y == CCPointZero.y) 
					|| (pHero->getPosition().getDistance(p) < pHero->getPosition().getDistance(intersectPoint))) {
						intersectPoint = p;
				}
				isIntersect = true;
				intersectPoint.x += 5;
		}
	}
	if (pHero->getPosition().x < line4Point1.x) {
		if (ccpSegmentIntersect(line4Point1, line4Point2
			, heroPosition, targetPosition)) {
				auto p = ccpIntersectPoint(line4Point1, line4Point2
					, heroPosition, targetPosition);
				if ((intersectPoint.x == CCPointZero.x && intersectPoint.y == CCPointZero.y) 
					|| (pHero->getPosition().getDistance(p) < pHero->getPosition().getDistance(intersectPoint))) {
						intersectPoint = p;
				}
				intersectPoint.x -= 5;
				isIntersect = true;
		}
	}
	if(isIntersect) {
		auto distance = pHero->getPosition().getDistance(intersectPoint);
		pTouch->retain();
		if (distance < 5) {				//���distance��С,ֱ���ƶ���ͼ���ƶ�Hero
			heroMoveComplete(pTouch);
		}
		else {
			auto pAction = 
				CCSequence::create(pHero->GetMoveToAction(intersectPoint)
				, CCCallFuncO::create(this, callfuncO_selector(MapLayer::heroMoveComplete), pTouch), NULL);
			pAction->setTag(PlayerSprite::kWalkActionTag);
			pHero->runAction(pAction);
		}
	}
	else {
		auto distance = pHero->getPosition().getDistance(pTouch->getLocation());
		auto moveby = pHero->GetMoveByActionByDistance(distance, pTouch->getLocation());
		auto sequence = CCSequence::createWithTwoActions(moveby, CCCallFunc::create(this, callfunc_selector(MapLayer::allMoveComplete)));
		sequence->setTag(moveby->getTag());
		pHero->runAction(sequence);
	}



}

void MapLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLayer::ccTouchCancelled(pTouch, pEvent);
}

CCNode* MapLayer::GetMapLayer()
{
	auto mapLayer = this->getChildByTag(kMapLayerTag);
	return mapLayer;
}

PlayerSprite* MapLayer::GetHeroSprite()
{
	auto pHeroSprite = this->getChildByTag(kMyHeroTag);
	return dynamic_cast<PlayerSprite*>(pHeroSprite);
}

void MapLayer::heroMoveComplete( CCObject* pTouch )
{
	auto designSize = CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize();
	auto pHero = GetHeroSprite();
	auto pMapLayer = GetMapLayer();
	auto pTouchReal = dynamic_cast<CCTouch*>(pTouch);
	auto movePoint = pHero->getPosition() - pTouchReal->getLocation();
	auto mapLayerPosition = pMapLayer->getPosition();
	CCPoint mapTarget = ccpAdd(mapLayerPosition, movePoint);
	CCPoint heroTarget;
	bool isEdge = false;
	if (mapTarget.x > 0 ) {
		heroTarget.x = pMapLayer->getPositionX() - mapTarget.x;
		mapTarget.x = 0;
		isEdge = true;
	}
	if (mapTarget.y > 0) {
		heroTarget.y = pMapLayer->getPositionY() - mapTarget.y;
		mapTarget.y = 0;
		isEdge = true;
	}
	if (mapTarget.x < -GetMapWidth() + designSize.width) {
		heroTarget.x = -(pMapLayer->getPositionX() + mapTarget.x + GetMapWidth() - designSize.width);
		mapTarget.x = -GetMapWidth() + designSize.width;
		isEdge = true;
	}
	if (mapTarget.y < -GetMapHeight() + designSize.height) {
		heroTarget.y = -(pMapLayer->getPositionY() + mapTarget.y + GetMapHeight() - designSize.height);
		mapTarget.y = -GetMapHeight() + designSize.height;
		isEdge = true;
	}
	auto pMove = CCMoveTo::create(pMapLayer->getPosition().getDistance(mapTarget) / pHero->GetSpeed(), mapTarget);
	//auto pMove = pHero->GetMoveByActionByDistance(pHero->getPosition().getDistance(mapTarget), mapTarget);
	if(isEdge) {
		pMapLayer->runAction(CCSequence::createWithTwoActions(pMove, CCCallFunc::create(this, callfunc_selector(MapLayer::allMoveComplete))));
		pHero->runAction(
			CCSequence::createWithTwoActions(
			CCDelayTime::create(pMove->getDuration()), 
			pHero->GetMoveToAction(pHero->getPosition() + heroTarget)));
	}
	else {
		auto sequence = CCSequence::createWithTwoActions(pMove, CCCallFunc::create(this, callfunc_selector(MapLayer::allMoveComplete)));
		sequence->setTag(pMove->getTag());
		pMapLayer->runAction(sequence);
	}
	pTouchReal->release();
}

void MapLayer::allMoveComplete()
{
	return ;
	auto pMapLayer = GetMapLayer();
	auto pHero = GetHeroSprite();
	auto designSize = CCDirector::sharedDirector()->getOpenGLView()->getDesignResolutionSize();
	auto screenCenterPoint = ccp(designSize.width / 2, designSize.height / 2);
	auto screenCenterDistance = pHero->getPosition().getDistance(screenCenterPoint);
	auto gotoScreenCenter = pHero->GetMoveByActionByDistance(screenCenterDistance, screenCenterPoint);
	gotoScreenCenter->setDuration(gotoScreenCenter->getDuration() * 3);
	auto gotoScreenCenterEase = CCEaseSineOut::create(gotoScreenCenter);
	gotoScreenCenterEase->setTag(kReverseToCenterPointActionTag);
	pMapLayer->runAction(gotoScreenCenterEase);
	pHero->runAction(dynamic_cast<CCEaseSineOut*>(gotoScreenCenterEase->copy()));
}



void MapLayer::draw()
{
// 
// 	//����Ƿ���OpenGL����������������ӡ����  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//���õ�Ĵ�С  
// 	ccPointSize(64);  
// 	//���ú���Ҫ���л���ʱ���õ�ɫ��  
// 	ccDrawColor4B(0,0,255,128);  
// 	//����һ����  
// 	ccDrawPoint( ccp(s.width / 2, s.height / 2) );  
// 	//����Ƿ���OpenGL����������������ӡ����  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	// �����ĸ���  
// 	//���ﴴ��λ�õ�����  
// 	CCPoint points[] = { ccp(60,60), ccp(70,70), ccp(60,70), ccp(70,60) };  
// 	ccPointSize(4);  
// 	//���ú���Ҫ���л���ʱ���õ�ɫ��  
// 	ccDrawColor4B(0,255,255,255);  
// 	//ʹ��λ�õ�������Ϊ�ĸ������λ�ý��л���  
// 	ccDrawPoints( points, 4);  
// 	//����Ƿ���OpenGL����������������ӡ����  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//����һ����ɫԲ  
// 	glLineWidth(16);  
// 	//���ú���Ҫ���л���ʱ���õ�ɫ��  
// 	ccDrawColor4B(0, 255, 0, 255);  
// 	//����Բ��������1�����ĵ㣬��2Ϊ�뾶,��3ΪԲ����ʱ����ת�Ƕȣ���4ΪԲ��ƽ���зֶ��������һ��������ָ���Ƿ��Բ�ֶ���ֹ��λ����Բ�������ߣ����ﲻ��������  
// 	ccDrawCircle( ccp(s.width/2,  s.height/2), 100, 0, 10, false);  
// 	//����Ƿ���OpenGL����������������ӡ����  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//����һ����ɫԲ,��������  
// 	glLineWidth(2);  
// 	//���ú���Ҫ���л���ʱ���õ�ɫ��  
// 	ccDrawColor4B(0, 255, 255, 255);  
// 	//����ʹ����һ����CC_DEGREES_TO_RADIANS�ѽǶ�ֵתΪ���ȡ�ת����90�ȣ�Ŀ����Ϊ�����������ߴ�ֱ��ʾ��  
// 	ccDrawCircle( ccp(s.width/2, s.height/2), 50, CC_DEGREES_TO_RADIANS(90), 50, true);  
// 	//�������  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	// ���ƶ�����߿�  
// 	ccDrawColor4B(255, 255, 0, 255);  
// 	glLineWidth(10);  
// 	CCPoint vertices[] = { ccp(0,0), ccp(50,50), ccp(100,50), ccp(100,100), ccp(50,100) };  
// 	//������ƶ�����߿�����ʹ������Ķ���������Ϊ������߿�Ķ���λ�ã��ڶ�������Ϊ��������������������ָ���Ƿ���β�Զ������γɷ���߿�  
// 	//ע����ʵ�������������������ȽϺ�,һ����ȥ�����һ��������ccDrawPoly�����ڻ���Ĭ�Ϸ�յĶ�����߿���һ��ccDrawLineList���ڻ����߶��С�  
// 	ccDrawPoly( vertices, 5, false);  
// 	//�������  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//����ʵ������  
// 	glLineWidth(1);  
// 	CCPoint filledVertices[] = { ccp(0,120), ccp(50,120), ccp(50,170), ccp(25,200), ccp(0,170) };  
// 	//��������ڲ����ָ��ɫ�ʵĶ����  
// 	ccDrawSolidPoly(filledVertices, 5, ccc4f(0.5f, 0.5f, 1, 1 ) );  
// 
// 	// ���Ʒ�ն�����߿�������Ǹ��������߿��ˡ�  
// 	ccDrawColor4B(255, 0, 255, 255);  
// 	glLineWidth(2);  
// 	CCPoint vertices2[] = { ccp(30,130), ccp(30,230), ccp(50,200) };  
// 	ccDrawPoly( vertices2, 3, true);  
// 
// 	CHECK_GL_ERROR_DEBUG();  
	auto pDirector = CCDirector::sharedDirector();
	auto designSize = pDirector->getOpenGLView()->getDesignResolutionSize();
	CCPoint line1Point1 = ccp(0, m_heroMoveRect.getMinY());
	CCPoint line1Point2 = ccp(designSize.width, m_heroMoveRect.getMinY());
	CCPoint line2Point1 = ccp(0, m_heroMoveRect.getMaxY());
	CCPoint line2Point2 = ccp(designSize.width, m_heroMoveRect.getMaxY());
	CCPoint line3Point1 = ccp(m_heroMoveRect.getMinX(), 0);
	CCPoint line3Point2 = ccp(m_heroMoveRect.getMinX(), designSize.height);
	CCPoint line4Point1 = ccp(m_heroMoveRect.getMaxX(), 0);
	CCPoint line4Point2 = ccp(m_heroMoveRect.getMaxX(), designSize.height);

	//�����߿�
	glLineWidth( 5.0f );  
	//���ú���Ҫ���л���ʱ���õ�ɫ��  
	ccDrawColor4B(255,0,0,255);
	ccDrawLine(line1Point1, line1Point2);
	ccDrawLine(line2Point1, line2Point2);
	ccDrawLine(line3Point1, line3Point2);
	ccDrawLine(line4Point1, line4Point2);
}