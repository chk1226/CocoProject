#ifndef _ROLE_H_
#define _ROLE_H_

#include <memory>
#include "cocos2d.h"
#include "Game\MovementComponent.h"
#include "Game\RotateNodeComponent.h"

namespace MyGame
{
	extern const std::string RoleSpriteName;

	class MovementComponent;
	class RotateNodeComponent;
	class Role : public cocos2d::Node
	{
	public:
		//Role();
		//~Role();

		enum State
		{
			Alive,
			Fail
		};

		std::function<void(int)> ScoreIncreateCallback;

		static Role* CreateRole();

		virtual bool init() override;
		virtual void update(float delta) override;

		void OnTouchBegin();
		void RegisterTouchBeginListener(std::function<void()> func);
		State GetState() { return m_state; }

	private:
		MyGame::MovementComponent* cacheMovement;
		MyGame::RotateNodeComponent* cacheRotateNode;
		State m_state;
		std::string passFlowNum;

		std::vector<std::function<void()>> m_TouchBeginListenerList;
		bool onContactBegin(cocos2d::PhysicsContact& contact);
		void gameOver();


		CREATE_FUNC(Role);
	};

	//Role::Role()
	//{
	//	
	//}

	//Role::~Role()
	//{
	//}




}




#endif
