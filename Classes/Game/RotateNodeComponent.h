#ifndef _ROTATE_NODE_COMPONENT_H_
#define _ROTATE_NODE_COMPONENT_H_

#include <memory>
#include "cocos2d.h"
#include "Game\Role.h"
#include "Game\MovementComponent.h"
namespace MyGame
{
	class MovementComponent;
	class RotateNodeComponent : public cocos2d::Component
	{
	public:
		//RotateNodeComponent(cocos2d::Node* master, std::weak_ptr<MovementComponent> movement);

		virtual void update(float delta) override;
		virtual bool init() override;
		
		//static RotateNodeComponent* create( MovementComponent* movement);
		void Setup(MovementComponent* movement);

		//~RotateNodeComponent();
		CREATE_FUNC(RotateNodeComponent);
	private:
		cocos2d::Node* cacheRoleImage;
		MovementComponent* cacheMovement;

	};

	
/*
	RotateNodeComponent::~RotateNodeComponent()
	{
	}*/

}



#endif