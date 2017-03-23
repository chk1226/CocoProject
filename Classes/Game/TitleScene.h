#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "cocos2d.h"
#include "Game\InGameScene.h"
#include "Game\Map.h"
#include "Game\ScoreBoard.h"


namespace MyGame
{
	class TitleScene : public cocos2d::Layer
	{
	public:
		//ScoreBoard* BoardPage;

		static cocos2d::Scene* CreateScene();

		virtual bool init() override;
		
		~TitleScene();
	private:
		cocos2d::Layer* cacheGUILayer;
		cocos2d::Layer* cacheObstacleLayer;
		cocos2d::Layer* cacheBackgroundLayer;
		cocos2d::Layer* cacheTerrainLayer;
		cocos2d::Layer* cacheMapLayer;
		cocos2d::ui::Scale9Sprite* m_startButton;
		cocos2d::ui::Scale9Sprite* m_rankButton;
		cocos2d::EventListenerTouchOneByOne* m_listener;
		cocos2d::EventListenerTouchOneByOne* m_rankListener;


		Map* cacheMap;


		void onStartGame();
		void menuSetup();
		void mapLayerInit();
		void onRankDialog();

		//// implement the create() method manually
		CREATE_FUNC(TitleScene);
	};

}




#endif
