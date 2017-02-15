#include "Game\InGameScene.h"
#include "Game\Resource.h"
#include "ui\CocosGUI.h"
#include "Game\Logger.h"
#include "Game\GameoverDialog.h"

namespace MyGame
{
	USING_NS_CC;

	Scene* InGameScene::CreateScene()
	{
		auto scene = Scene::createWithPhysics();
		if (!scene)
		{
			return nullptr;
		}

		scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		
		auto layer = InGameScene::create();
		scene->addChild(layer);


		return scene;
	}

	bool InGameScene::init()
	{
		// base init
		if (!Layer::init())
		{
			return false;
		}

		m_score = 0;

		// add schedule update
		this->scheduleUpdate();

		// initial layer
		cacheMapLayer = Layer::create();
		this->addChild(cacheMapLayer);
		cacheBackgroundLayer = Layer::create();
		this->addChild(cacheBackgroundLayer);
		cacheObstacleLayer = Layer::create();
		this->addChild(cacheObstacleLayer);
		cacheTerrainLayer = Layer::create();
		this->addChild(cacheTerrainLayer);
		cacheRoleLayer = Layer::create();
		this->addChild(cacheRoleLayer);
		cacheGUILayer = Layer::create();
		this->addChild(cacheGUILayer);

		guiLayerInit();
		roleLayerInit();
		mapLayerInit();
		

		return true;
		
	}

	void InGameScene::update(float delta)
	{
		if (cacheRole->GetState() == Role::State::Fail &&
			cacheMap->GetState() == Map::State::Run)
		{
			cacheMap->SetState(Map::State::Stop);

			//show gameover dialog
			auto dialog = GameoverDialog::create();
			dialog->Setup(m_score);
			cacheGUILayer->addChild(dialog);

			if (m_jumpWidget)
			{
				m_jumpWidget->setEnabled(false);
			}
		}


	}

	void InGameScene::ScoreIncreate(int value)
	{
		m_score += value;
		score->setString(MyFramework::Convert(m_score));
	}

	InGameScene::~InGameScene()
	{
	}


	void InGameScene::guiLayerInit()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		// add touch region
		m_jumpWidget = cocos2d::ui::Widget::create();
		m_jumpWidget->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
		m_jumpWidget->setContentSize(Size(visibleSize.width, visibleSize.height));
		m_jumpWidget->setTouchEnabled(true);
		
		m_jumpWidget->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				
				for (auto it = m_TouchBeganCallbackList.begin(); it != m_TouchBeganCallbackList.end(); ++it)
				{
					(*it)();
				}

				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				break;
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}
		
		});

		cacheGUILayer->addChild(m_jumpWidget);

		//add sorce
		score = Label::createWithTTF(ResourceInstance->PixelBlockConfig, MyFramework::Convert(m_score));
		score->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 150));


		cacheGUILayer->addChild(score);
	}


	void InGameScene::roleLayerInit()
	{
		cacheRole = Role::CreateRole();
		m_TouchBeganCallbackList.push_back(std::bind(&Role::OnTouchBegin, cacheRole));
		cacheRole->ScoreIncreateCallback = CC_CALLBACK_1(InGameScene::ScoreIncreate, this);

		cacheRoleLayer->addChild(cacheRole);
	}

	void InGameScene::mapLayerInit()
	{
		cacheMap = Map::CreateMap();
		cacheMapLayer->addChild(cacheMap);
		cacheMap->CacheBackgroundLayer = cacheBackgroundLayer;
		cacheMap->CacheTerrainLayer = cacheTerrainLayer;
		cacheMap->CacheObstacleLayer = cacheObstacleLayer;
		cacheMap->SetUp();
	}







}



