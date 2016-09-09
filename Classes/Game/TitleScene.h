#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_
#include "cocos2d.h"
#include "Game\InGameScene.h"

namespace MyGame
{
	class TitleScene : public cocos2d::Scene
	{
	public:
		static cocos2d::Scene* CreateScene();


		virtual bool init();
		
		//// implement the create() method manually
		CREATE_FUNC(TitleScene);

	private:
		cocos2d::Layer* cacheMiddleLayer;

		void onStartGame();
		void startButtonInit();
	};

}




#endif
