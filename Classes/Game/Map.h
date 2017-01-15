#ifndef _MAP_H_
#define _MAP_H_

#include "cocos2d.h"

namespace MyGame
{
	extern const std::string RoleSpriteName;

	class Map : public cocos2d::Node
	{
	public:
		//Role();
		//~Role();

		static Map* CreateMap();

		virtual bool init() override;
		virtual void update(float delta) override;

		void SetUp();

		/*void AddComponent(std::shared_ptr<BaseComponent> cmp);
		void OnTouchBegin();

		void RegisterTouchBeginListener(std::function<void()> func);
*/
		//cocos2d::Layer* CacheTerrainLayer;

	private:

		//std::vector<std::shared_ptr<BaseComponent>> m_ComponentList;
		//std::vector<std::function<void()>> m_TouchBeginListenerList;

		//bool onContactBegin(cocos2d::PhysicsContact& contact);

		CREATE_FUNC(Map);
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