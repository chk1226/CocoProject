#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include <memory>
#include "cocos2d.h"

namespace MyGame
{ 

	const int RoleBitmask = 1;
	const int TerrainBitmask = 2;
	const int PassBitmask = 3;
	const int ObstacleBitmask = 4;


	class Resource
	{
	public:

		enum EBackgroundSet
		{
			B_1 = 1,
			B_2,
			B_3,
			B_4
		}BackgroundSet = B_1;


		const char* FloorBlueTMX = "tiled/floor_blue.tmx";
		const char* BackgroundSetHill = "set%d_hills.png";
		const char* BackgroundSetTiles = "set%d_tiles.png";
		const char* ObstacleName = "doorOpen";
		const char* ObstacleEndName = "doorOpen_top";
		const char* PassName = "tileBlue_08";


		const cocos2d::Color3B B_1c = cocos2d::Color3B(216, 191, 158);

		struct SpriteFileName
		{
			std::string Square1x1;
			std::string Option;
			std::string Bird;
			std::string Floor;
		};

		const SpriteFileName& GetSpriteName();
		cocos2d::SpriteFrame* GetCharacterSpriteFrame(std::string filename);
		cocos2d::SpriteFrame* GetCoreSpriteFrame(std::string filename);
		cocos2d::SpriteFrame* GetBackgroundFrame(std::string filename);
		const cocos2d::Color3B& GetBackgroundColor();


		~Resource();
		static void Create();
	private:

		cocos2d::SpriteFrameCache* const m_Character = cocos2d::SpriteFrameCache::getInstance();
		cocos2d::SpriteFrameCache* const m_Core = cocos2d::SpriteFrameCache::getInstance();
		cocos2d::SpriteFrameCache* const m_Background = cocos2d::SpriteFrameCache::getInstance();

		SpriteFileName SpriteName;


		Resource();
	};

	extern std::shared_ptr<Resource> ResourceInstance;

}






//Resource::~Resource()
//{
//}



#endif //_RESOURCE_H_