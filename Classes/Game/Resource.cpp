#include "Game\Resource.h"
#include "Game\Logger.h"
#include "Framework\Utility.h"

namespace MyGame
{

	std::shared_ptr<Resource> ResourceInstance;


	cocos2d::SpriteFrame* Resource::GetCharacterSpriteFrame(int id)
	{
		cocos2d::SpriteFrame* spriteFrame = nullptr;
		if(m_Character)
		{
			char buff[50];
			snprintf(buff, sizeof(buff), BirdSpriteName, id);
			spriteFrame = m_Character->getSpriteFrameByName(buff);
		}
		return spriteFrame;
	}

	cocos2d::SpriteFrame * Resource::GetCoreSpriteFrame(std::string filename)
	{
		cocos2d::SpriteFrame* spriteFrame = nullptr;
		if (m_Core)
		{
			spriteFrame = m_Core->getSpriteFrameByName(filename + ".png");
		}
		return spriteFrame;
	}

	cocos2d::SpriteFrame * Resource::GetBackgroundFrame(std::string filename)
	{
		cocos2d::SpriteFrame* spriteFrame = nullptr;
		if (m_Background)
		{
			spriteFrame = m_Background->getSpriteFrameByName(filename);
		}
		return spriteFrame;
	}

	cocos2d::SpriteFrame * Resource::GetUIFrame(std::string filename)
	{
		cocos2d::SpriteFrame* spriteFrame = nullptr;
		if (m_UI)
		{
			spriteFrame = m_UI->getSpriteFrameByName(filename);
		}
		return spriteFrame;
	}

	std::string Resource::GetTerrainSetName()
	{
		std::string name = "";
		switch (TerrainSet)
		{
		case ETerrainSet::Green:
			name = "Green";
			break;
		case ETerrainSet::Blue:
			name = "Blue";
			break;
		case ETerrainSet::Yellow:
			name = "Yellow";
			break;
		default:
			break;
		}
		return name;
	}

	std::string Resource::GetObstacleSetName()
	{
		std::string name = "";
		switch (ObstacleSet)
		{
		case EObstacleSet::Green:
			name = "Green";
			break;
		case EObstacleSet::Open:
			name = "Open";
			break;
		case EObstacleSet::Red:
			name = "Red";
			break;
		default:
			break;
		}
		return name;
	}

	const cocos2d::Color3B & Resource::GetBackgroundColor()
	{
		switch (BackgroundSet)
		{
		case EBackgroundSet::B_1:
			return B_1c;
		case EBackgroundSet::B_2:
			return B_2c;
		case EBackgroundSet::B_3:
			return B_3c;
		case EBackgroundSet::B_4:
			return B_4c;
		default:
			return cocos2d::Color3B::WHITE;
			
		}
	}

	void Resource::SaveFile(std::string data)
	{
		auto fileUtils = cocos2d::FileUtils::getInstance();
		auto path = fileUtils->getWritablePath();

		//MyLog(path.c_str());

		if (!fileUtils->isDirectoryExist(path))
		{
			if (!fileUtils->createDirectory(path))
			{
				MyLog("create directory fail");
				return;
			}
		}

		if (data.length() <= 0)
		{
			return;
		}

		if (!fileUtils->writeStringToFile(data, path + DataFileName))
		{
			MyLog("save fail");

		}
	}

	std::string Resource::LoadFile()
	{
		auto fileUtils = cocos2d::FileUtils::getInstance();
		auto path = fileUtils->getWritablePath();

		if (!fileUtils->isDirectoryExist(path))
		{
			MyLog("load file fail, no this directory");

			return "0";
		}

		auto data = fileUtils->getStringFromFile(path + DataFileName);
		
		return (data.length() <= 0) ? "0" : data;
	}

	Resource::~Resource()
	{
		
	}

	void Resource::Create() {
		ResourceInstance = std::shared_ptr<Resource>(new Resource());
	}

	Resource::Resource()
	{
		// load sprite sheet	
		if (m_Character) 
		{
			std::string plistStr = "character.plist";
			m_Character->addSpriteFramesWithFile(plistStr);
		}

		if (m_Core)
		{
			std::string plistStr = "core.plist";
			m_Core->addSpriteFramesWithFile(plistStr);
		}

		if (m_Background)
		{
			std::string plistStr = "background.plist";
			m_Background->addSpriteFramesWithFile(plistStr);
		}

		if (m_UI)
		{
			std::string plistStr = "ui.plist";
			m_UI->addSpriteFramesWithFile(plistStr);

		}


		// font setup
		PixelBlockConfig.fontFilePath = "fonts/kenpixel_blocks.ttf";
		PixelBlockConfig.fontSize = 70;

		PixelFutureConfig.fontFilePath = "fonts/kenvector_future_thin.ttf";



	}
}