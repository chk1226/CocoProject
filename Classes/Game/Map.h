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
		~Map();

		static Map* CreateMap();

		virtual bool init() override;
		virtual void update(float delta) override;

		void SetUp();

		cocos2d::Layer* CacheTerrainLayer;
		cocos2d::Layer* CacheObstacleLayer;
		cocos2d::Layer* CacheBackgroundLayer;


	private:

		TMXLoader* floorTmx;
		std::vector<cocos2d::Node*> m_TerrainGroup;
		std::vector<cocos2d::Node*> m_RegTerrainGroup;	// for register
		std::vector<cocos2d::Node*> m_BackgroundTilesGroup;
		std::vector<cocos2d::Node*> m_BackgroundHillGroup;
		cocos2d::Sprite* m_Obstacle;
		std::vector<cocos2d::Node*> m_ObstacleList;
		cocos2d::Sprite* m_ObstacleEnd;
		std::vector<cocos2d::Node*> m_ObstacleEndList;
		cocos2d::Sprite* m_Pass;
		std::vector<cocos2d::Node*> m_PassList;

		int appearDistance;

		void terrainMove(float delta);
		void backgroundMove(float delta);
		void obstacleMove(float delta);

		//bool onContactBegin(cocos2d::PhysicsContact& contact);



		CREATE_FUNC(Map);
	};





}


#endif