#ifndef _MOVEMENT_COMPONENT_H_
#define _MOVEMENT_COMPONENT_H_

#include "Game\BaseComponent.h"
#include "Game\Role.h"
#include "Framework\Utility.h"
namespace MyGame
{
	extern const float BurstVelocity;
	extern const float GravityVelocity;

	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent(cocos2d::Node* master);

		virtual void Update(float delta) override;

		void InjectBurst();
		const cocos2d::Vec2& GetCurrentVelocity();

		enum State
		{
			Gravity,
			Burst
		};
		//~MovementComponent();
	private:
		float m_ToVecloityY;
		float m_Frequence;
		State m_State;
		cocos2d::Vec2 m_CurrentVelocity;

		void gravityCalculate(float delta);
	};



	//MovementComponent::~MovementComponent()
	//{
	//}




}



#endif