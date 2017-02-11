#include "RotateNodeComponent.h"
#include "Framework\Utility.h"

namespace MyGame
{

	USING_NS_CC;

	void RotateNodeComponent::update(float delta)
	{
		if (!isEnabled()) return;

		if (cacheRoleImage)
		{
			auto movement = cacheMovement;
			if (movement)
			{
				auto velocity = movement->GetCurrentVelocity();

				float angle = 0;
				if (velocity.y >= 0) 
				{
					angle = MyFramework::Lerp(0, 60, velocity.y / BurstVelocity);
				}
				else
				{
					angle = MyFramework::Lerp(0, -80, velocity.y / GravityVelocity);
				}

				cacheRoleImage->setRotation(0);
				cacheRoleImage->setRotation(-angle);

			}

		}
	}

	bool RotateNodeComponent::init()
	{
		if (!Component::init())
		{
			return false;
		}
		setName("RotateNodeComponent");
		return true;
	}

	void RotateNodeComponent::Setup(MovementComponent* movement)
	{

		auto owner = getOwner();
		if (owner)
		{
			cacheRoleImage = owner->getChildByName(RoleSpriteName);
		}
		cacheMovement = movement;
	}


}

