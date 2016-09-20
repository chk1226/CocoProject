#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_
#include "cocos2d.h"
#include "Game\InGameScene.h"

namespace MyGame
{
	class TitleScene : public cocos2d::Scene
	{
	public:
		static TitleScene* CreateScene();


		virtual bool init() override;
		

	private:
		cocos2d::Layer* cacheMiddleLayer;

		void onStartGame();
		void startButtonInit();
		//// implement the create() method manually
		CREATE_FUNC(TitleScene);
	};

}




#endif
