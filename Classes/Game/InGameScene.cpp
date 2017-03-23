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

#ifdef MYGAME_DEBUG
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif // mygame
		
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
			showGameOver();
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
		TTFConfig fontConfig(ResourceInstance->TTFPixelFuturePath, 70);
		score = Label::createWithTTF(fontConfig, MyFramework::Convert(m_score));
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
		
		//rand map
		auto r = ResourceInstance;
		r->BackgroundSet = static_cast<Resource::EBackgroundSet>(RandomHelper::random_int<int>(1, static_cast<int>(Resource::EBackgroundSet::All) - 1));
		r->TerrainSet = static_cast<Resource::ETerrainSet>(RandomHelper::random_int<int>(0, static_cast<int>( Resource::ETerrainSet::All) - 1));
		r->ObstacleSet = static_cast<Resource::EObstacleSet>(RandomHelper::random_int<int>(0, static_cast<int>( Resource::EObstacleSet::All) - 1));


		cacheMap->SetUp();
	}

	int SET_SHAKE_DURATION;
	void InGameScene::showGameOver()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		
		auto r = ResourceInstance;
		auto mask = Sprite::createWithSpriteFrame(r->GetUIFrame(r->UI4x4W));
		mask->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		mask->setScale(1000);
		mask->setOpacity(1);
		cacheGUILayer->addChild(mask, 0, "white_mask");
		
		auto seq = Sequence::create(FadeIn::create(0.1f), 
			FadeOut::create(0.1f), 
			DelayTime::create(0.2f), 
			CallFunc::create([this] {
			
			cacheGUILayer->removeChildByName("white_mask");

			auto dialog = GameoverDialog::create();
			dialog->Setup(m_score);
			cacheGUILayer->addChild(dialog);

			if (m_jumpWidget)
			{
				m_jumpWidget->setEnabled(false);
			}
		
		}),
			CallFunc::create([this] {
			this->score->runAction(FadeOut::create(0.15f));
		}),
			nullptr);
		mask->runAction(seq);

		// shake
		m_initialPos = this->getPosition();
		SET_SHAKE_DURATION = 18;
		this->schedule(schedule_selector(InGameScene::shakeScreen));
		

	}

	void InGameScene::shakeScreen(float dt)
	{
		float randx = MyFramework::RangeRandom(-50.0f, 50.0);
		float randy = MyFramework::RangeRandom(-50.0f, 50.0);

		this->setPosition(Point(randx, randy));
		this->setPosition(Point(m_initialPos.x + randx, m_initialPos.y + randy));

		SET_SHAKE_DURATION -= 1;

		if (SET_SHAKE_DURATION <= 0)
		{
			this->setPosition(Point(m_initialPos.x, m_initialPos.y));
			this->unschedule(schedule_selector(InGameScene::shakeScreen));
		}
	}







}



