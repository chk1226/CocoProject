#include "Game\TitleScene.h"
#include "Game\Resource.h"
#include "ui\CocosGUI.h"

namespace MyGame
{

	USING_NS_CC;

	Scene* TitleScene::CreateScene()
	{

		auto scene = Scene::createWithPhysics();
		if (!scene)
		{
			return nullptr;
		}

		scene->getPhysicsWorld()->setGravity(Vec2::ZERO);

		auto layer = TitleScene::create();
		scene->addChild(layer);


		return scene;
	}

	bool TitleScene::init()
	{
		// base init
		if (!Layer::init())
		{
			return false;
		}

		// initial layer
		cacheMapLayer = Layer::create();
		this->addChild(cacheMapLayer);
		cacheBackgroundLayer = Layer::create();
		this->addChild(cacheBackgroundLayer);
		cacheObstacleLayer = Layer::create();
		this->addChild(cacheObstacleLayer);
		cacheTerrainLayer = Layer::create();
		this->addChild(cacheTerrainLayer);
		cacheGUILayer = Layer::create();
		this->addChild(cacheGUILayer);

		mapLayerInit();
		menuSetup();

		return true;
	}

	TitleScene::~TitleScene()
	{
		if (m_listener)
		{
			Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
		}
	}


	void TitleScene::menuSetup()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		// title button
		auto buttonSize = Size(180, 80);

		m_startButton = ui::Scale9Sprite::createWithSpriteFrame(ResourceInstance->GetUIFrame(ResourceInstance->UIGreenButtonName));
		m_startButton->setCapInsets(Rect(5, 5, 9, 16));
		m_startButton->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2 - 100));
		m_startButton->setContentSize(buttonSize);
		cacheGUILayer->addChild(m_startButton);

		m_listener = EventListenerTouchOneByOne::create();
		m_listener->setSwallowTouches(true);
		m_listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			Vec2 p = touch->getLocation();
			cocos2d::Rect rect = m_startButton->getBoundingBox();

			if (m_startButton->getParent())
			{
				auto w_origin = m_startButton->getParent()->convertToWorldSpace(rect.origin);
				rect.origin = w_origin;
			}


			if (rect.containsPoint(p))
			{
				return true; // to indicate that we have consumed it.
			}

			return false; // we did not consume this event, pass thru.
		};

		m_listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			// start game
			onStartGame();

		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_listener, 30);

		auto fontConfig = ResourceInstance->PixelFutureConfig;
		fontConfig.fontSize = 28;
		auto label = Label::createWithTTF(fontConfig, "Start");
		label->setTextColor(Color4B::BLACK);
		label->setPosition(buttonSize.width / 2, buttonSize.height / 2);
		m_startButton->addChild(label);

	}

	void TitleScene::onStartGame()
	{
		auto inGameScene = InGameScene::CreateScene();
		auto director = Director::getInstance();
		director->replaceScene(inGameScene);

	}

	void TitleScene::mapLayerInit()
	{
		cacheMap = Map::CreateMap();
		cacheMapLayer->addChild(cacheMap);
		cacheMap->CacheBackgroundLayer = cacheBackgroundLayer;
		cacheMap->CacheTerrainLayer = cacheTerrainLayer;
		cacheMap->CacheObstacleLayer = cacheObstacleLayer;

		cacheMap->SetUp();
		cacheMap->ObstacleEnable = false;
	}



}