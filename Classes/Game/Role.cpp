#include "Game\Role.h"
#include "Game\Logger.h"
#include "Game\Resource.h"

namespace MyGame
{

	USING_NS_CC;

	const std::string RoleSpriteName = "role_image";

	Role* Role::CreateRole()
	{
		auto node = Role::create();
		return node;
	}

	bool Role::init()
	{
		if (!Node::init())
		{
			return false;
		}

		this->scheduleUpdate();

		// sate init
		m_state = State::Alive;

		passFlowNum = "";

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		this->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));


		// add sprite
		auto roelName = ResourceInstance->BirdSpriteName;
		int frameNum = 4;
		if (ResourceInstance->EnableBlueRole)
		{
			roelName = ResourceInstance->BluePlayerSpriteName;
			frameNum = 5;
		}

		Vector<SpriteFrame*> animFrame(frameNum);
		for (int i = 0; i < 4; i++)
		{
			auto frame = ResourceInstance->GetCharacterSpriteFrame(roelName, i + 1);
			if (frame)
			{
				animFrame.pushBack(frame);
			}
		}

		auto animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
		auto animate = Animate::create(animation);
		
		roleSprite = Sprite::createWithSpriteFrame(ResourceInstance->GetCharacterSpriteFrame(roelName, 1));
		if (!ResourceInstance->EnableBlueRole)
		{
			roleSprite->setScale(0.25f);
		}
		roleSprite->runAction(RepeatForever::create(animate));

		auto spriteSize = roleSprite->getContentSize();

		if (!ResourceInstance->EnableBlueRole)
		{
			spriteSize.width -= 40;
			spriteSize.height -= 40; 
		}
		auto physicsBody = PhysicsBody::createBox(spriteSize, PhysicsMaterial(0, 0, 0));
		physicsBody->setContactTestBitmask(RoleBitmask);
		physicsBody->setDynamic(true);
		
		roleSprite->setPhysicsBody(physicsBody);


		this->addChild(roleSprite, 0, RoleSpriteName);

		//add contact event listener
		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_1(Role::onContactBegin, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
		
		// add movement component
		cacheMovement = MovementComponent::create();
		this->addComponent(cacheMovement);
		RegisterTouchBeginListener(std::bind(&MovementComponent::InjectBurst, cacheMovement));
		
		// add rotation node component
		cacheRotateNode = RotateNodeComponent::create();
		this->addComponent(cacheRotateNode);
		cacheRotateNode->Setup(cacheMovement);

		return true;

	}

	void Role::update(float delta)
	{
		cocos2d::Node::update(delta);
	}


	void Role::OnTouchBegin()
	{
		for (auto it = m_TouchBeginListenerList.begin(); it != m_TouchBeginListenerList.end(); ++it)
		{
			(*it)();
		}
	}

	void Role::RegisterTouchBeginListener(std::function<void()> func)
	{
		m_TouchBeginListenerList.push_back(func);
	}

	bool Role::onContactBegin(PhysicsContact & contact)
	{
		PhysicsBody *a = contact.getShapeA()->getBody();
		PhysicsBody *b = contact.getShapeB()->getBody();

		// check if the bodies have collided
		if ((RoleBitmask == a->getContactTestBitmask() && TerrainBitmask == b->getContactTestBitmask()) ||
			(TerrainBitmask == a->getContactTestBitmask() && RoleBitmask == b->getContactTestBitmask()))
		{
			ResourceInstance->AudioEffectPlay(ResourceInstance->FXPunch);
			// game over
			gameOver();

			MyLog("TERRAIN COLLISION HAS OCCURED");
			return true;
		}

		if ((RoleBitmask == a->getContactTestBitmask() && ObstacleBitmask == b->getContactTestBitmask()) ||
			(ObstacleBitmask == a->getContactTestBitmask() && RoleBitmask == b->getContactTestBitmask()))
		{
			ResourceInstance->AudioEffectPlay(ResourceInstance->FXPunch);

			// game over
			gameOver();

			MyLog("OBSTACLE COLLISION HAS OCCURED");
			return true;
		}

		if ((RoleBitmask == a->getContactTestBitmask() && PassBitmask == b->getContactTestBitmask()) ||
			(PassBitmask == a->getContactTestBitmask() && RoleBitmask == b->getContactTestBitmask()))
		{
			// pass
			std::string passName;
			if (a->getContactTestBitmask() == PassBitmask)
			{
				passName = a->getOwner()->getName();
			}
			else
			{
				passName = b->getOwner()->getName();
			}

			if (passFlowNum.compare(passName) != 0)
			{
				ResourceInstance->AudioEffectPlay(ResourceInstance->FXCoin);

				if (ScoreIncreateCallback)
				{
					ScoreIncreateCallback(1);
				}

				passFlowNum = passName;
				MyLog("*Pass COLLISION HAS OCCURED*");
				return false;
			}


		}

		return false;
	}

	void Role::gameOver()
	{
		if (cacheMovement)
		{
			cacheMovement->setEnabled(false);
		}

		if (cacheRotateNode)
		{
			cacheRotateNode->setEnabled(false);
		}

		if (roleSprite)
		{
			roleSprite->stopAllActions();
		}
		m_state = State::Fail;
	}


}