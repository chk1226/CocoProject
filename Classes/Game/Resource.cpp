#include "Game\Resource.h"

namespace MyGame
{

	std::shared_ptr<Resource> ResourceInstance;

	//Resource::Resource()
	//{
	//
	//}
	
	const Resource::SpriteFileName& Resource::GetSpriteName()
	{
		return SpriteName;
	}

	void Resource::Create() {
		ResourceInstance = std::shared_ptr<Resource>(new Resource());
	}

	Resource::Resource()
	{
		// sprite file name
		SpriteName.Square1x1 = "original1x1.png";
		SpriteName.Option = "option.png";
		SpriteName.Bird = "Frame-1.png";
	}
}