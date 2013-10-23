#include "PlayerSprite.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

bool PlayerSprite::init()
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/EnemyAnimation0.png", "animations/EnemyAnimation0.plist", "animations/tauren.ExportJson");
	CCArmature* armature = CCArmature::create("tauren");
	armature->getAnimation()->play("loading");
	this->addChild(armature);
	armature->setPosition(ccp(0, 0));
	m_speed = 100 / 1.0f;
	setAnchorPoint(ccp(0.5f, 0.25f));
	return true;
}

CCMoveTo* PlayerSprite::GetMoveToActionByDistance( float distance, const CCPoint& target )
{
	auto pMoveTo = CCMoveTo::create(distance / m_speed, target);
	pMoveTo->setTag(kWalkActionTag);
	return pMoveTo;
}

CCMoveBy* PlayerSprite::GetMoveByActionByDistance( float distance, const CCPoint& target )
{
	auto pMoveBy = CCMoveBy::create(distance / m_speed, target - this->getPosition());
	pMoveBy->setTag(kWalkActionTag);
	return pMoveBy;
}

CCMoveBy* PlayerSprite::GetMoveByActionByDistanceForMap( float distance, const CCPoint& target )
{
	auto pMoveBy = CCMoveBy::create(distance / m_speed, this->getPosition() - target);
	pMoveBy->setTag(kWalkActionTag);
	return pMoveBy;
}
