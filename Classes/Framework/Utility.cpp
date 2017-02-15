#include "Framework\Utility.h"


std::string MyFramework::Convert(float num)
{
	std::ostringstream buff;
	buff << num;
	return buff.str();
}

std::string MyFramework::Convert(int num)
{
	return std::to_string(num);
}

float MyFramework::Lerp(float a, float b, float f)
{
	return a + f *(b - a);
}

cocos2d::Node * MyFramework::CloneCCNode(cocos2d::Node * source)
{

	auto clone = cocos2d::Node::create();
	auto children = source->getChildren();

	clone->setRotationQuat(source->getRotationQuat());
	clone->setPosition(source->getPosition());
	clone->setAnchorPoint(source->getAnchorPoint());
	clone->setContentSize(source->getContentSize());
	clone->setZOrder(source->getZOrder());

	for (auto it = children.begin(); it != children.end(); ++it)
	{
		cocos2d::Node* subNode = CloneSingleCCNode((*it));

		if (subNode)
		{
			clone->addChild(subNode);
		}

	}

	return clone;
}

cocos2d::Node * MyFramework::CloneSingleCCNode(cocos2d::Node* source)
{
	cocos2d::Node* node;
	if (source == nullptr)
	{
		return node;
	}

	if (auto sprite = dynamic_cast<cocos2d::Sprite*>(source))
	{
		auto subSprite = cocos2d::Sprite::create();
		subSprite->setSpriteFrame(sprite->getSpriteFrame());
		
		auto physics = sprite->getPhysicsBody();
		if (physics)
		{
			auto clonePhysicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize(), cocos2d::PhysicsMaterial(0, 0, 0));
			clonePhysicsBody->setContactTestBitmask(physics->getContactTestBitmask());
			clonePhysicsBody->setDynamic(physics->isDynamic());
			subSprite->setPhysicsBody(clonePhysicsBody);

		}

		node = subSprite;
	}
	else
	{
		node = cocos2d::Node::create();
	}

	node->setRotationQuat(source->getRotationQuat());
	node->setPosition(source->getPosition());
	node->setAnchorPoint(source->getAnchorPoint());
	node->setContentSize(source->getContentSize());
	node->setZOrder(source->getZOrder());
	node->setVisible(source->isVisible());

	return node;
}


bool MyFramework::ToBool(std::string str) {
	if (str.length() != 0)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		std::istringstream is(str);
		bool b;
		is >> std::boolalpha >> b;
		return b;
	}
	
	return false;
}
