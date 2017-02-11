#include "Game\Resource.h"

namespace MyGame
{

	std::shared_ptr<Resource> ResourceInstance;

	
	const Resource::SpriteFileName& Resource::GetSpriteName()
	{
		return SpriteName;
	}

	cocos2d::SpriteFrame* Resource::GetCharacterSpriteFrame(std::string filename)
	{
		cocos2d::SpriteFrame* spriteFrame;
		if(m_Character)
		{
			 spriteFrame = m_Character->getSpriteFrameByName(filename);
		}
		return spriteFrame;
	}

	cocos2d::SpriteFrame * Resource::GetCoreSpriteFrame(std::string filename)
	{
		cocos2d::SpriteFrame* spriteFrame;
		if (m_Core)
		{
			spriteFrame = m_Core->getSpriteFrameByName(filename + ".png");
		}
		return spriteFrame;
	}

	cocos2d::SpriteFrame * Resource::GetBackgroundFrame(std::string filename)
	{
		cocos2d::SpriteFrame* spriteFrame;
		if (m_Character)
		{
			spriteFrame = m_Background->getSpriteFrameByName(filename);
		}
		return spriteFrame;
	}

	const cocos2d::Color3B & Resource::GetBackgroundColor()
	{
		switch (BackgroundSet)
		{
		case EBackgroundSet::B_1:
			return B_1c;
		default:
			return cocos2d::Color3B::WHITE;
			
		}
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


		// sprite file name
		SpriteName.Square1x1 = "original1x1.png";
		SpriteName.Option = "option.png";
		SpriteName.Bird = "Frame-1.png";
		SpriteName.Floor = "tileBlue_22.png";
	}
}