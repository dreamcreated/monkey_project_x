#include "MapLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MapLayer::SetMapID( int mapid )
{
	//TODO 忽略掉地图ID,只载入一个地图
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
	auto mapLayer = this->getChildByTag(kMapLayerTag);
	return mapLayer->getContentSize().width;
}

int MapLayer::GetMapHeight()
{
	auto mapLayer = this->getChildByTag(kMapLayerTag);
	return mapLayer->getContentSize().height;
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
	GetMapLayer()->stopActionByTag(PlayerSprite::kWalkActionTag);

	auto distance = pHero->getPosition().getDistance(pTouch->getLocation());

	float s, t;
// 	CCPoint leftTopPoint = ccp(m_heroMoveRect.getMinX(), m_heroMoveRect.getMaxY());
// 	CCPoint rightTopPoint = ccp(m_heroMoveRect.getMaxX(), m_heroMoveRect.getMaxY());
// 	CCPoint leftBottomPoint = ccp(m_heroMoveRect.getMinX(), m_heroMoveRect.getMinY());
// 	CCPoint rightBottomPoint = ccp(m_heroMoveRect.getMaxX(), m_heroMoveRect.getMinY());

	CCPoint line1Point1 = ccp(0, m_heroMoveRect.getMinY()); //下方的线段
	CCPoint line1Point2 = ccp(designSize.width, m_heroMoveRect.getMinY());	//下方的线段
	CCPoint line2Point1 = ccp(0, m_heroMoveRect.getMaxY());			//上方的线段
	CCPoint line2Point2 = ccp(designSize.width, m_heroMoveRect.getMaxY());	//上方的线段
	CCPoint line3Point1 = ccp(m_heroMoveRect.getMinX(), 0);			//左方线段
	CCPoint line3Point2 = ccp(m_heroMoveRect.getMinX(), designSize.height);	//左方线段
	CCPoint line4Point1 = ccp(m_heroMoveRect.getMaxX(), 0);				//右方线段
	CCPoint line4Point2 = ccp(m_heroMoveRect.getMaxX(), designSize.height);		//右方线段


	bool isIntersect = false;
	CCPoint intersectPoint;
	CCPoint heroPosition = pHero->getPosition();
	CCPoint targetPosition = pTouch->getLocation();
	
	if (ccpSegmentIntersect(line1Point1, line1Point2
		, heroPosition, targetPosition)) {
			intersectPoint = ccpIntersectPoint(line1Point1, line1Point2
				, heroPosition, targetPosition);
			isIntersect = true;
			intersectPoint.x += 5;
	}
	else if (ccpSegmentIntersect(line2Point1, line2Point2
		, heroPosition, targetPosition)) {
			intersectPoint = ccpIntersectPoint(line2Point1, line2Point2
				, heroPosition, targetPosition);
			isIntersect = true;
			intersectPoint.x -= 5;
	}
	else if (ccpSegmentIntersect(line3Point1, line3Point2
		, heroPosition, targetPosition)) {
			intersectPoint = ccpIntersectPoint(line3Point1, line3Point2
				, heroPosition, targetPosition);
			isIntersect = true;
			intersectPoint.y += 5;
	}
	else if (ccpSegmentIntersect(line4Point1, line4Point2
		, heroPosition, targetPosition)) {
			intersectPoint = ccpIntersectPoint(line4Point1, line4Point2
				, heroPosition, targetPosition);
			intersectPoint.y -= 5;
			isIntersect = true;
	}
	else {			//目标点和移动框内四条线段都没有相交
		pHero->runAction(pHero->GetMoveByActionByDistance(distance, pTouch->getLocation()));
	}
	if(isIntersect) {
		pTouch->retain();
		auto pAction = 
			CCSequence::create(pHero->GetMoveByActionByDistance(distance, intersectPoint)
			, CCCallFuncO::create(this, callfuncO_selector(MapLayer::heroMoveComplete), pTouch), NULL);
		pAction->setTag(PlayerSprite::kWalkActionTag);
		pHero->runAction(pAction);
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
	auto pHero = GetHeroSprite();
	auto pMapLayer = GetMapLayer();
	auto pTouchReal = dynamic_cast<CCTouch*>(pTouch);
	auto pMove = pHero->GetMoveByActionByDistanceForMap(pHero->getPosition().getDistance(pTouchReal->getLocation()), pTouchReal->getLocation());
	pMapLayer->runAction(pMove);
	pTouchReal->release();
}

void MapLayer::draw()
{
// 
// 	//检测是否有OpenGL错误发生，如果有则打印错误  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//设置点的大小  
// 	ccPointSize(64);  
// 	//设置后面要进行绘制时所用的色彩  
// 	ccDrawColor4B(0,0,255,128);  
// 	//绘制一个点  
// 	ccDrawPoint( ccp(s.width / 2, s.height / 2) );  
// 	//检测是否有OpenGL错误发生，如果有则打印错误  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	// 绘制四个点  
// 	//这里创建位置点数组  
// 	CCPoint points[] = { ccp(60,60), ccp(70,70), ccp(60,70), ccp(70,60) };  
// 	ccPointSize(4);  
// 	//设置后面要进行绘制时所用的色彩  
// 	ccDrawColor4B(0,255,255,255);  
// 	//使用位置点数组做为四个顶点的位置进行绘制  
// 	ccDrawPoints( points, 4);  
// 	//检测是否有OpenGL错误发生，如果有则打印错误  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//绘制一个绿色圆  
// 	glLineWidth(16);  
// 	//设置后面要进行绘制时所用的色彩  
// 	ccDrawColor4B(0, 255, 0, 255);  
// 	//绘制圆函数，参1是中心点，参2为半径,参3为圆的逆时针旋转角度，参4为圆的平均切分段数，最后一个参数是指定是否从圆分段起止点位置向圆中心连线，这里不进行连线  
// 	ccDrawCircle( ccp(s.width/2,  s.height/2), 100, 0, 10, false);  
// 	//检测是否有OpenGL错误发生，如果有则打印错误  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//绘制一个蓝色圆,进行连线  
// 	glLineWidth(2);  
// 	//设置后面要进行绘制时所用的色彩  
// 	ccDrawColor4B(0, 255, 255, 255);  
// 	//这里使用了一个宏CC_DEGREES_TO_RADIANS把角度值转为弧度。转动了90度，目的是为了让中心连线垂直显示。  
// 	ccDrawCircle( ccp(s.width/2, s.height/2), 50, CC_DEGREES_TO_RADIANS(90), 50, true);  
// 	//继续检错  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	// 绘制多边形线框。  
// 	ccDrawColor4B(255, 255, 0, 255);  
// 	glLineWidth(10);  
// 	CCPoint vertices[] = { ccp(0,0), ccp(50,50), ccp(100,50), ccp(100,100), ccp(50,100) };  
// 	//这里绘制多边形线框函数，使用上面的顶点数组做为多边形线框的顶点位置，第二个参数为顶点数量，第三个参数指定是否首尾自动连接形成封闭线框。  
// 	//注：其实这个函数拆成两个函数比较好,一个是去掉最后一个参数的ccDrawPoly，用于绘制默认封闭的多边形线框。另一个ccDrawLineList用于绘制线段列。  
// 	ccDrawPoly( vertices, 5, false);  
// 	//继续检错  
// 	CHECK_GL_ERROR_DEBUG();  
// 
// 	//绘制实体多边形  
// 	glLineWidth(1);  
// 	CCPoint filledVertices[] = { ccp(0,120), ccp(50,120), ccp(50,170), ccp(25,200), ccp(0,170) };  
// 	//这里绘制内部填充指定色彩的多边形  
// 	ccDrawSolidPoly(filledVertices, 5, ccc4f(0.5f, 0.5f, 1, 1 ) );  
// 
// 	// 绘制封闭多边形线框，这里就是个三角形线框了。  
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

	//设置线宽
	glLineWidth( 5.0f );  
	//设置后面要进行绘制时所用的色彩  
	ccDrawColor4B(255,0,0,255);
	ccDrawLine(line1Point1, line1Point2);
	ccDrawLine(line2Point1, line2Point2);
	ccDrawLine(line3Point1, line3Point2);
	ccDrawLine(line4Point1, line4Point2);
}

