#ifndef _ROLE_H_
#define _ROLE_H_

#include <memory>
#include "cocos2d.h"
#include "Game\MovementComponent.h"
#include "Game\RotateNodeComponent.h"

namespace MyGame
{
	extern const std::string RoleSpriteName;

	class Role : public cocos2d::Node
	{
	public:
		//Role();
		//~Role();

		static Role* CreateRole();

		virtual bool init() override;
		virtual void update(float delta) override;

		void AddComponent(std::shared_ptr<BaseComponent> cmp);
		void OnTouchBegin();

		void RegisterTouchBeginListener(std::function<void()> func);

	private:

		std::vector<std::shared_ptr<BaseComponent>> m_ComponentList;
		std::vector<std::function<void()>> m_TouchBeginListenerList;

		bool onContactBegin(cocos2d::PhysicsContact& contact);

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
