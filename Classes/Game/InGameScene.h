#ifndef _INGAME_SCENE_H_
#define _INGAME_SCENE_H_

#include "cocos2d.h"
#include "Game\TitleScene.h"
#include "Game\Role.h"

namespace MyGame
{
	class InGameScene : public cocos2d::Scene
	{
	public:
		typedef std::function<void()> TouchBeganCallback;

		static InGameScene* CreateScene();

		virtual bool init() override;

		InGameScene::~InGameScene();
	private:

		cocos2d::Layer* cacheRoleLayer;
		cocos2d::Layer* cacheGUILayer;
		std::vector<TouchBeganCallback> m_TouchBeganCallbackList;

		void guiLayerInit();
		void roleLayerInit();
		void returnTitleScene();

		//// implement the create() method manually
		CREATE_FUNC(InGameScene);
	};

	//InGameScene::InGameScene()
	//{
	//}

	//{
	//}


}



#endif
