#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include <memory>
#include "cocos2d.h"

namespace MyGame
{ 
	class Resource
	{
	public:
		struct SpriteFileName
		{
			std::string Square1x1;
			std::string Option;
		};

		const SpriteFileName& GetSpriteName();

		//~Resource();
		static void Create();
	private:

		SpriteFileName SpriteName;


		Resource();
	};
	extern std::shared_ptr<Resource> ResourceInstance;
}






//Resource::~Resource()
//{
//}



#endif //_RESOURCE_H_