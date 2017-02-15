#include "GameoverDialog.h"
#include "Game\Resource.h"
#include "Framework\Utility.h"
#include "ui\CocosGUI.h"
#include "Game\Logger.h"

namespace MyGame
{

	USING_NS_CC;

	GameoverDialog::~GameoverDialog()
	{
		if (m_listener)
		{
			Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
		}

	}

	bool GameoverDialog::init()
	{
		if (!Node::init())
		{
			return false;
		}

		this->m_listener = nullptr;

		return true;
	}

	void GameoverDialog::Setup(int score)
	{

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		this->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50));


		// show game over text
		auto fontConfig = ResourceInstance->PixelFutureConfig;
		fontConfig.fontSize = 60;
		auto label = Label::createWithTTF(fontConfig, "GAME OVER");
		label->setPosition(Vec2(0, 200));
		this->addChild(label);

		// show sorce
		auto image = ui::Scale9Sprite::createWithSpriteFrame(ResourceInstance->GetUIFrame(ResourceInstance->UIFieldBGName));
		image->setCapInsets(Rect(20, 20, 60, 60));
		image->setContentSize(Size(350, 250));
		this->addChild(image);

		// title button
		auto buttonSize = Size(150, 50);

		m_titleButton = ui::Scale9Sprite::createWithSpriteFrame(ResourceInstance->GetUIFrame(ResourceInstance->UIGreenButtonName));
		m_titleButton->setCapInsets(Rect(5, 5, 9, 16));
		m_titleButton->setPosition(Vec2(-100, -180));
		m_titleButton->setContentSize(buttonSize);
		this->addChild(m_titleButton);

		m_listener = EventListenerTouchOneByOne::create();
		m_listener->setSwallowTouches(true);
		m_listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			Vec2 p = touch->getLocation();
			cocos2d::Rect rect = m_titleButton->getBoundingBox();

			auto w_origin = this->convertToWorldSpace(rect.origin);
			rect.origin = w_origin;
			

			if (rect.containsPoint(p))
			{
				return true; // to indicate that we have consumed it.
			}

			return false; // we did not consume this event, pass thru.
		};

		m_listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			MyLog("ccccccc");

			returnTitleScene();

		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_listener, 30);

		fontConfig.fontSize = 28;
		label = Label::createWithTTF(fontConfig, "Title");
		label->setTextColor(Color4B::BLACK);
		label->setPosition(buttonSize.width/2, buttonSize.height/2);
		m_titleButton->addChild(label);
		
	}

	void GameoverDialog::returnTitleScene()
	{
		auto titleScene = TitleScene::CreateScene();
		auto director = Director::getInstance();
		director->replaceScene(titleScene);
	}

}

