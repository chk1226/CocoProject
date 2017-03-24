#include "Game\TitleScene.h"
#include "Game\Resource.h"
#include "ui\CocosGUI.h"
#include "Game\Logger.h"

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

		ResourceInstance->EnableBlueRole = false;

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

		if (m_rankListener)
		{
			Director::getInstance()->getEventDispatcher()->removeEventListener(m_rankListener);
		}

		if (m_blueListener)
		{
			Director::getInstance()->getEventDispatcher()->removeEventListener(m_blueListener);
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
		m_listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			if (cacheGUILayer->getChildByName("rank"))
			{
				return false;
			}

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
			ResourceInstance->AudioEffectPlay(ResourceInstance->FXClick);

			// start game
			onStartGame();

		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_listener, 30);

		TTFConfig fontConfig(ResourceInstance->TTFPixelFuturePath, 28);
		auto label = Label::createWithTTF(fontConfig, "Start");
		label->setTextColor(Color4B::BLACK);
		label->setPosition(buttonSize.width / 2, buttonSize.height / 2);
		m_startButton->addChild(label);

		// Rank button
		m_rankButton = ui::Scale9Sprite::createWithSpriteFrame(ResourceInstance->GetUIFrame(ResourceInstance->UIYellowButtonName));
		m_rankButton->setCapInsets(Rect(5, 5, 9, 16));
		m_rankButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 200));
		m_rankButton->setContentSize(buttonSize);
		cacheGUILayer->addChild(m_rankButton);

		m_rankListener = EventListenerTouchOneByOne::create();
		m_rankListener->setSwallowTouches(true);
		m_rankListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			if (cacheGUILayer->getChildByName("rank"))
			{
				return false;
			}


			Vec2 p = touch->getLocation();
			cocos2d::Rect rect = m_rankButton->getBoundingBox();

			if (m_rankButton->getParent())
			{
				auto w_origin = m_rankButton->getParent()->convertToWorldSpace(rect.origin);
				rect.origin = w_origin;
			}


			if (rect.containsPoint(p))
			{
				return true; // to indicate that we have consumed it.
			}

			return false; // we did not consume this event, pass thru.
		};

		m_rankListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			ResourceInstance->AudioEffectPlay(ResourceInstance->FXClick);

			// show rank
			onRankDialog();
		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_rankListener, 30);

		label = Label::createWithTTF(fontConfig, "Rank");
		label->setTextColor(Color4B::BLACK);
		label->setPosition(buttonSize.width / 2, buttonSize.height / 2);
		m_rankButton->addChild(label);


		// show guid
		auto guid = ResourceInstance->LoadFile(Resource::FileType::GUID);
		if (!guid.compare("0"))
		{
			char buff[1000] = { 0 };
			sprintf(buff, "%x%x-%x-%x",
				cocos2d::random(), cocos2d::random(),                 // Generates a 64-bit Hex number
				((cocos2d::random() & 0x0fff) | 0x4000),   // Generates a 32-bit Hex number of the form 4xxx (4 indicates the UUID version)
				cocos2d::random() % 0x3fff + 0x8000);       // Generates a 32-bit Hex number in the range [0x8000, 0xbfff]
	
			guid = std::string(buff);

			//GUID pguid;
			//CoCreateGuid(&pguid);
			//// Convert the GUID to a string
			//wchar_t* bstrGuid;
			//StringFromCLSID(pguid, &bstrGuid);
			//std::wstring w_s(bstrGuid);
			//guid = std::string(w_s.begin(), w_s.end());
			//MyLog(guid.c_str());
			//::CoTaskMemFree(bstrGuid);
			
			ResourceInstance->SaveFile(Resource::FileType::GUID, guid);
		}
		else
		{
			guid = ResourceInstance->LoadFile(Resource::FileType::GUID);
		}

		fontConfig.fontSize = 14;
		label = Label::createWithTTF(fontConfig, guid);
		label->setTextColor(Color4B::BLACK);
		label->setAnchorPoint(Vec2::UNIT_X);
		label->setPosition(origin.x + visibleSize.width, 10);
		cacheGUILayer->addChild(label);

		// show version
		label = Label::createWithTTF(fontConfig, "Version:1.0.0");
		label->setTextColor(Color4B::BLACK);
		label->setAnchorPoint(Vec2::UNIT_X);
		label->setPosition(origin.x + visibleSize.width, 30);
		cacheGUILayer->addChild(label);

		// easter egg
		easterEgg(label->getContentSize().width);
		
	}

	void TitleScene::onStartGame()
	{
		ResourceInstance->StopAllAudio();
		this->stopAllActions();
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

	void TitleScene::onRankDialog()
	{
		auto BoardPage = ScoreBoard::create();
		cacheGUILayer->addChild(BoardPage, 0, "rank");

	}

	void TitleScene::easterEgg(float width)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		// add sprite
		Vector<SpriteFrame*> animFrame(5);
		for (int i = 0; i < 5; i++)
		{
			auto frame = ResourceInstance->GetCharacterSpriteFrame(ResourceInstance->BluePlayerSpriteName, i + 1);
			if (frame)
			{
				animFrame.pushBack(frame);
			}
		}

		auto animation = Animation::createWithSpriteFrames(animFrame, 0.1f);
		auto animate = Animate::create(animation);

		blueRole = Sprite::createWithSpriteFrame(ResourceInstance->GetCharacterSpriteFrame(ResourceInstance->BluePlayerSpriteName, 1));
		blueRole->runAction(RepeatForever::create(animate));
		auto rSize = blueRole->getContentSize();
		blueRole->setPosition(origin.x + visibleSize.width - width - rSize.height/2, 30 + rSize.width/2);
		cacheGUILayer->addChild(blueRole);

		//set touch
		m_blueListener = EventListenerTouchOneByOne::create();
		m_blueListener->setSwallowTouches(true);
		m_blueListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			Vec2 p = touch->getLocation();
			cocos2d::Rect rect = this->blueRole->getBoundingBox();

			if (this->blueRole->getParent())
			{
				auto w_origin = this->blueRole->getParent()->convertToWorldSpace(rect.origin);
				rect.origin = w_origin;
			}

			if (rect.containsPoint(p))
			{
				return true; // to indicate that we have consumed it.
			}

			return false; // we did not consume this event, pass thru.
		};

		m_blueListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)
		{

			auto seq = Sequence::create(/*CallFunc::create([] {
				ResourceInstance->AudioEffectPlay(ResourceInstance->FXMusicBox);
			}),
				DelayTime::create(15),*/
				CallFunc::create([this] {
				ResourceInstance->AudioEffectPlay(ResourceInstance->FXCheer);
				ResourceInstance->EnableBlueRole = true;
				blueRole->runAction(FadeOut::create(0.3f));
			}), nullptr);
			this->runAction(seq);
			
			if (m_blueListener)
			{
				Director::getInstance()->getEventDispatcher()->removeEventListener(m_blueListener);
				m_blueListener = nullptr;
			}

		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_blueListener, 30);

	}



}