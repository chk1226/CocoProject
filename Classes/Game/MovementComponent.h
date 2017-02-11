#ifndef _MOVEMENT_COMPONENT_H_
#define _MOVEMENT_COMPONENT_H_

#include "Game\Role.h"
#include "Framework\Utility.h"
namespace MyGame
{
	extern const float BurstVelocity;
	extern const float GravityVelocity;

	class MovementComponent : public cocos2d::Component
	{
	public:

		virtual void update(float) override;
		virtual bool init() override;
		//static MovementComponent* create();

		void InjectBurst();
		void Setup();
		const cocos2d::Vec2& GetCurrentVelocity();

		enum State
		{
			Gravity,
			Burst
		};
		//~MovementComponent();
		
		CREATE_FUNC(MovementComponent);
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