#ifndef _INGAME_SCENE_H_
#define _INGAME_SCENE_H_

#include "cocos2d.h"
#include "Game\TitleScene.h"

namespace MyGame
{
	class InGameScene : public cocos2d::Scene
	{
	public:
		static cocos2d::Scene* CreateScene();

		virtual bool init();

		//// implement the create() method manually
		CREATE_FUNC(InGameScene);
	private:

		cocos2d::Layer* cacheCharacterLayer;
		cocos2d::Layer* cacheGUILayer;


		void guiInit();
		void returnTitleScene();
	};

	//InGameScene::InGameScene()
	//{
	//}

	//InGameScene::~InGameScene()
	//{
	//}



}



#endif
