#include "Framework\Utility.h"
#include <sstream>
#include <iostream>

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


int MyFramework::atoi(const std::string& str)
{
	int numb;
	std::istringstream(str) >> numb;
	return numb;
}

int MyFramework::atoi_16(const std::string & str)
{
	std::stringstream stream;
	stream << str;
	int value;
	stream >> std::hex >> value;

	return value;
}

bool MyFramework::ToBool(std::string str) {
	
	if (str.length() != 0)
	{
		if (str.compare("bool") == 0)
		{
			return true;
		}
		//std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		//std::istringstream is(str);
		//bool b;
		//is >> std::boolalpha >> b;
		//return b;
	}
	
	return false;
}

float MyFramework::RangeRandom(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return rnd*(max - min) + min;
}
