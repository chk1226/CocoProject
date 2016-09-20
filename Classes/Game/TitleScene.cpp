#include "Game\TitleScene.h"
#include "Game\Resource.h"
#include "ui\CocosGUI.h"

namespace MyGame
{

	USING_NS_CC;

	TitleScene* TitleScene::CreateScene()
	{
		auto scene = TitleScene::create();

		return scene;
	}

	bool TitleScene::init()
	{
		// base init
		if (!Scene::init())
		{
			return false;
		}

		// initial layer
		cacheMiddleLayer = Layer::create();
		this->addChild(cacheMiddleLayer);

		startButtonInit();


		///////////////////////////////
		//// 3. add your codes below...

		//// add a label shows "Hello World"
		//// create and initialize a label

		//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

		//// position the label on the center of the screen
		//label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		//	origin.y + visibleSize.height - label->getContentSize().height));

		//// add the label as a child to this layer
		//this->addChild(label, 1);


		return true;
	}


	void TitleScene::startButtonInit()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto spriteName = ResourceInstance->GetSpriteName();

		auto node = Node::create();
		node->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5));

		auto sprite = Sprite::create(spriteName.Square1x1);
		sprite->setTextureRect(Rect(0, 0, 160, 90));

		auto startButton = ui::Button::create();
		startButton->setTitleText("Start");
		startButton->setTitleFontSize(52);
		startButton->setTitleColor(Color3B::BLACK);
		startButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			ui::Button* button = dynamic_cast<ui::Button*>(sender);
			if (button == nullptr || button->getParent() == nullptr)
			{
				return;
			}
			auto bg = dynamic_cast<Sprite*>(button->getParent()->getChildByName("bg"));;

			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				if (bg)
				{
					bg->setColor(Color3B::GRAY);
				}
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				if (bg)
				{
					bg->setColor(Color3B::WHITE);
				}

				onStartGame();
				break;
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				if (bg)
				{
					bg->setColor(Color3B::WHITE);
				}

				break;
			default:
				break;
			}

		});

		node->addChild(sprite, 0, "bg");
		node->addChild(startButton);



		if (cacheMiddleLayer != nullptr)
		{
			cacheMiddleLayer->addChild(node);

		}
	
	
	}

	void TitleScene::onStartGame()
	{
		auto inGameScene = InGameScene::CreateScene();
		auto director = Director::getInstance();
		director->replaceScene(inGameScene);

	}



}