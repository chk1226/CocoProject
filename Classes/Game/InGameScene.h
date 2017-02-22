#ifndef _INGAME_SCENE_H_
#define _INGAME_SCENE_H_

#include "cocos2d.h"
#include "Game\TitleScene.h"
#include "Game\Role.h"
#include "Game\Map.h"

namespace MyGame
{
	class InGameScene : public cocos2d::Layer
	{
	public:
		typedef std::function<void()> TouchBeganCallback;

		static cocos2d::Scene* CreateScene();

		virtual bool init() override;
		virtual void update(float delta) override;
		void ScoreIncreate(int value);

		~InGameScene();
	private:

		cocos2d::Layer* cacheRoleLayer;
		cocos2d::Layer* cacheGUILayer;
		cocos2d::Layer* cacheTerrainLayer;
		cocos2d::Layer* cacheObstacleLayer;
		cocos2d::Layer* cacheBackgroundLayer;
		cocos2d::Layer* cacheMapLayer;
		Role* cacheRole;
		Map* cacheMap;
		cocos2d::Label* score;
		cocos2d::ui::Widget* m_jumpWidget;
		int m_score;


		std::vector<TouchBeganCallback> m_TouchBeganCallbackList;

		void guiLayerInit();
		void roleLayerInit();
		void mapLayerInit();


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
