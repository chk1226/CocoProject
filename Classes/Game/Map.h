#ifndef _MAP_H_
#define _MAP_H_

#include "cocos2d.h"
#include "Framework\Utility.h"
#include "Framework\TMXLoader\TMXLoader.h"

namespace MyGame
{
	extern const std::string RoleSpriteName;

	class Map : public cocos2d::Node
	{
	public:
		//Role();
		~Map();

		static Map* CreateMap();

		virtual bool init() override;
		virtual void update(float delta) override;

		void SetUp();

		/*void AddComponent(std::shared_ptr<BaseComponent> cmp);
		void OnTouchBegin();

		void RegisterTouchBeginListener(std::function<void()> func);
*/
		cocos2d::Layer* CacheTerrainLayer;
		cocos2d::Layer* CacheBackgroundLayer;


	private:

		TMXLoader* floorTmx;
		std::vector<cocos2d::Node*> m_TerrainGroup;
		std::vector<cocos2d::Node*> m_RegTerrainGroup;	// for register
		std::vector<cocos2d::Node*> m_BackgroundTilesGroup;
		std::vector<cocos2d::Node*> m_BackgroundHillGroup;

		void terrainMove(float delta);
		void backgroundMove(float delta);

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