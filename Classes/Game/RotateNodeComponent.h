#ifndef _ROTATE_NODE_COMPONENT_H_
#define _ROTATE_NODE_COMPONENT_H_

#include <memory>
#include "cocos2d.h"
#include "Game\Role.h"
#include "Game\MovementComponent.h"
namespace MyGame
{
	class MovementComponent;
	class RotateNodeComponent : public BaseComponent
	{
	public:
		RotateNodeComponent(cocos2d::Node* master, std::weak_ptr<MovementComponent> movement);

		virtual void Update(float delta) override;


		//~RotateNodeComponent();

	private:
		cocos2d::Node* cacheRoleImage;

		std::weak_ptr<MyGame::MovementComponent> cacheMovement;
	};

	
/*
	RotateNodeComponent::~RotateNodeComponent()
	{
	}*/

}



#endif