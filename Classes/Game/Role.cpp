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


		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		this->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));


		// add sprite
		auto spriteName = ResourceInstance->GetSpriteName();
		auto image = Sprite::create(spriteName.Bird);
		image->setScale(0.25f);
		this->addChild(image, 0, RoleSpriteName);

		// add movement component
		auto movement = std::shared_ptr<MovementComponent>(new MovementComponent(this));
		auto cmp = std::dynamic_pointer_cast<BaseComponent>(movement);
		AddComponent(cmp);
		RegisterTouchBeginListener(std::bind(&MovementComponent::InjectBurst, movement));
		
		// add rotation node component
		auto rotateNode = std::shared_ptr<RotateNodeComponent>(new RotateNodeComponent(this, movement));
		cmp = std::dynamic_pointer_cast<BaseComponent>(rotateNode);
		AddComponent(cmp);
		

		return true;

	}

	void Role::update(float delta)
	{
		for (auto it = m_ComponentList.begin(); it != m_ComponentList.end(); ++it)
		{
			if ((*it))
			{
				(*it)->Update(delta);
			}
		}
	}


	void Role::AddComponent(std::shared_ptr<BaseComponent> cmp)
	{
		m_ComponentList.push_back(cmp);

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


}