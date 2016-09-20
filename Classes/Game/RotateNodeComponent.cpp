#include "RotateNodeComponent.h"
#include "Framework\Utility.h"

namespace MyGame
{

	USING_NS_CC;

	RotateNodeComponent::RotateNodeComponent(Node * master, std::weak_ptr<MovementComponent> movement) : BaseComponent(master)
	{
		if (master == nullptr) return;

		cacheRoleImage = master->getChildByName(RoleSpriteName);
		cacheMovement = movement;
	}

	void RotateNodeComponent::Update(float delta)
	{
		if (cacheRoleImage)
		{
			auto movement = cacheMovement.lock();
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


}

