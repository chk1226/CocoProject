#include "Map.h"
#include "Game\Resource.h"

namespace MyGame
{
	USING_NS_CC;

	Map * Map::CreateMap()
	{
		auto node = Map::create();

		return node;
	}

	bool Map::init()
	{
		if (!Node::init())
		{
			return false;
		}

		this->scheduleUpdate();

		SetUp();

		return true;
	}

	void Map::update(float delta)
	{
	}

	void Map::SetUp()
	{

		auto spriteName = ResourceInstance->GetSpriteName();
		auto image = Sprite::createWithSpriteFrame(ResourceInstance->GetCoreSpriteFrame(spriteName.Floor));

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		image->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.width / 5));
			
		auto physicsBody = PhysicsBody::createBox(image->getContentSize(), PhysicsMaterial(0, 0, 0));
		physicsBody->setContactTestBitmask(TerrainBitmask);
		physicsBody->setDynamic(false);

		image->setPhysicsBody(physicsBody);

		this->addChild(image, 0, "terrain");
	

	}



}

