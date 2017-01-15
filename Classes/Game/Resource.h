#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include <memory>
#include "cocos2d.h"

namespace MyGame
{ 

	const int RoleBitmask = 1;
	const int TerrainBitmask = 2;


	class Resource
	{
	public:
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


		~Resource();
		static void Create();
	private:

		cocos2d::SpriteFrameCache* const m_Character = cocos2d::SpriteFrameCache::getInstance();
		cocos2d::SpriteFrameCache* const m_Core = cocos2d::SpriteFrameCache::getInstance();

		SpriteFileName SpriteName;


		Resource();
	};

	extern std::shared_ptr<Resource> ResourceInstance;

}






//Resource::~Resource()
//{
//}



#endif //_RESOURCE_H_