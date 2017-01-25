#include "Game\MovementComponent.h"
#include "Game\Logger.h"

namespace MyGame
{

	const float BurstVelocity = 500.f;
	const float GravityVelocity = -500.f;


	MovementComponent::MovementComponent(cocos2d::Node* master) : BaseComponent(master)
	{
		if (m_Master == nullptr) return;

		m_ToVecloityY = GravityVelocity;
		m_State = State::Gravity;
	}

	

	void MovementComponent::Update(float delta)
	{
		if (!Enable) return;
		if (m_Master == nullptr) return;

		if (m_State == State::Gravity)
		{
			gravityCalculate(delta);
		}

		float rate = 4;
		m_CurrentVelocity.y = MyFramework::Lerp(m_CurrentVelocity.y, m_ToVecloityY, m_Frequence * delta * rate);

		//MyLog("m_Velocity : %f", m_CurrentVelocity.y);


		m_Master->setPositionY(m_Master->getPositionY() + m_CurrentVelocity.y * delta);


		if (m_State == State::Burst)
		{
			if (m_CurrentVelocity.y <= 10.f)
			{
				m_State = State::Gravity;
			}
		}


	}

	//void Movement::OnTouchBegin()
	//{
	//	MyLog("******Burst*******");
	//	injectBurst();
	//}

	void MovementComponent::gravityCalculate(float delta)
	{
		m_ToVecloityY = GravityVelocity;
		m_Frequence = 0.3f;
		
	}

	void MovementComponent::InjectBurst()
	{
		if (!Enable)
		{
			return;
		}

		m_CurrentVelocity.y = BurstVelocity;
		m_ToVecloityY = 0;
		m_Frequence = 0.9f;
		m_State = State::Burst;
	}

	const cocos2d::Vec2 & MovementComponent::GetCurrentVelocity()
	{
		return m_CurrentVelocity;
	}



}
