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

		// c++ 11
		enum class EBackgroundSet
		{
			B_1 = 1,
			B_2,
			B_3,
			B_4,
			All
		}BackgroundSet = EBackgroundSet::B_1;

		enum class ETerrainSet
		{
			Green,
			Yellow,
			Blue,
			All
		}TerrainSet = ETerrainSet::Green;
		

		enum class EObstacleSet
		{
			Open,
			Red,
			Green,
			All
		}ObstacleSet = EObstacleSet::Open;

		const char* FloorBlueTMX = "tiled/floor_blue.tmx";
		const char* BackgroundSetHill = "set%d_hills.png";
		const char* BackgroundSetTiles = "set%d_tiles.png";
		const char* ObstacleName = "door%s";
		const char* ObstacleEndName = "door%s_top";
		const char* PassName = "tileBlue_08";
		const char* BirdSpriteName = "frame-%d.png";
		const char* UIFieldBGName = "metalPanel.png";
		const char* UIFieldBGPlateName = "metalPanel_plate.png";
		const char* UIFieldBGYellowName = "metalPanel_yellow.png";
		const char* UIGreenButtonName = "squareGreen.png";
		const char* UIRedButtonName = "squareRed.png";
		const char* UIYellowButtonName = "squareYellow.png";
		const char* UICloseName = "transparentLight45.png";
		const char* UI4x4W = "4x4.png";
		const char* DataFileName = "save";
		const char* GUIDFileName = "guid";
		const char* FXCoin = "audio/coins.mp3";
		const char* FXPunch = "audio/punch.mp3";
		const char* FXOh = "audio/oh.mp3";
		const char* FXClick = "audio/click.mp3";
		const char* FXJump = "audio/jump.mp3";



		const cocos2d::Color3B B_1c = cocos2d::Color3B(216, 191, 158);
		const cocos2d::Color3B B_2c = cocos2d::Color3B(84, 68, 123);
		const cocos2d::Color3B B_3c = cocos2d::Color3B(255, 239, 189);
		const cocos2d::Color3B B_4c = cocos2d::Color3B(142, 110, 83);
		
		//font
		const char* TTFPixelBlockPath = "fonts/kenpixel_blocks.ttf";
		const char* TTFPixelFuturePath = "fonts/kenvector_future_thin.ttf";

		cocos2d::SpriteFrame* GetCharacterSpriteFrame(int id);
		cocos2d::SpriteFrame* GetCoreSpriteFrame(std::string filename);
		cocos2d::SpriteFrame* GetBackgroundFrame(std::string filename);
		cocos2d::SpriteFrame* GetUIFrame(std::string filename);
		
		std::string GetTerrainSetName();
		std::string GetObstacleSetName();
		const cocos2d::Color3B& GetBackgroundColor();

		void AudioEffectPlay(const char* name);

		enum class FileType
		{
			GUID,
			Score
		};
		void SaveFile(FileType type, std::string data);
		std::string LoadFile(FileType type);


		~Resource();
		static void Create();
	private:

		cocos2d::SpriteFrameCache* const m_Character = cocos2d::SpriteFrameCache::getInstance();
		cocos2d::SpriteFrameCache* const m_Core = cocos2d::SpriteFrameCache::getInstance();
		cocos2d::SpriteFrameCache* const m_Background = cocos2d::SpriteFrameCache::getInstance();
		cocos2d::SpriteFrameCache* const m_UI = cocos2d::SpriteFrameCache::getInstance();
		Resource();
	};

	extern std::shared_ptr<Resource> ResourceInstance;

}






//Resource::~Resource()
//{
//}



#endif //_RESOURCE_H_