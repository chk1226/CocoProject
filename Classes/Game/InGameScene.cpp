#include "Game\InGameScene.h"
#include "Game\Resource.h"
#include "ui\CocosGUI.h"
#include "Game\Logger.h"

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


		// initial layer
		cacheMapLayer = Layer::create();
		this->addChild(cacheMapLayer);
		cacheBackgroundLayer = Layer::create();
		this->addChild(cacheBackgroundLayer);
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

	InGameScene::~InGameScene()
	{
	}


	void InGameScene::guiLayerInit()
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

		cacheGUILayer->addChild(optionButton, 1);

		// add touch region
		auto widget = cocos2d::ui::Widget::create();
		widget->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
		widget->setContentSize(Size(visibleSize.width, visibleSize.height));
		widget->setTouchEnabled(true);
		
		widget->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		
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

		cacheGUILayer->addChild(widget);

	}


	void InGameScene::roleLayerInit()
	{
		cacheRole = Role::CreateRole();
		m_TouchBeganCallbackList.push_back(std::bind(&Role::OnTouchBegin, cacheRole));

		cacheRoleLayer->addChild(cacheRole);
	}

	void InGameScene::mapLayerInit()
	{
		cacheMap = Map::CreateMap();
		cacheMapLayer->addChild(cacheMap);
		cacheMap->CacheBackgroundLayer = cacheBackgroundLayer;
		cacheMap->CacheTerrainLayer = cacheTerrainLayer;
		cacheMap->SetUp();
	}

	void InGameScene::returnTitleScene()
	{
		auto titleScene = TitleScene::CreateScene();
		auto director = Director::getInstance();
		director->replaceScene(titleScene);
	
	
	}






}



