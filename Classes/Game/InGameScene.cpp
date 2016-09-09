#include "Game\InGameScene.h"
#include "Game\Resource.h"
#include "ui\CocosGUI.h"

namespace MyGame
{
	USING_NS_CC;

	cocos2d::Scene* InGameScene::CreateScene()
	{
		auto scene = InGameScene::create();
		return scene;
	}

	bool InGameScene::init()
	{
		// base init
		if (!Scene::init())
		{
			return false;
		}

		// initial layer
		cacheCharacterLayer = Layer::create();
		this->addChild(cacheCharacterLayer);
		cacheGUILayer = Layer::create();
		this->addChild(cacheGUILayer);

		guiInit();


		return true;
		
	}


	void InGameScene::guiInit()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto spriteName = ResourceInstance->GetSpriteName();
		auto optionButton = ui::Button::create(spriteName.Option);
		optionButton->setScale(0.5f);
		optionButton->setPosition(Vec2(origin.x + visibleSize.width - 50, origin.y + visibleSize.height -70));

		optionButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {

			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				returnTitleScene();
				break;
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}

		});

		cacheGUILayer->addChild(optionButton);
	}


	void InGameScene::returnTitleScene()
	{
		auto titleScene = TitleScene::CreateScene();
		auto director = Director::getInstance();
		director->replaceScene(titleScene);
	
	
	}






}



