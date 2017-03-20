#include "ScoreBoard.h"
#include "network\HttpClient.h"
#include "Game\Resource.h"
#include "Game\Logger.h"
#include "ui\CocosGUI.h"
#include "Framework\Utility.h"

namespace MyGame
{
	USING_NS_CC;

	//RequestState ScoreBoard::requestState = RequestState::Idle;
	const Size boardSize = Size(350, 480);

	ScoreBoard::~ScoreBoard()
	{
		if (m_listener)
		{
			Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
		}
	}

	bool ScoreBoard::init()
	{
		if (!Node::init())
		{
			return false;
		}

		requestState = RequestState::Idle;

		getTopData();

		//this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([this]() {
		//	if (requestState == RequestState::Fail)
		//	{
		//		//if (this->getParent())
		//		//{
		//		//	this->getParent()->removeChild(this);
		//		//}
		//		this->ShowFailUI();
		//	}

		//	this->WaitShow = false;
		//}), NULL));

		return true;
	}

	void ScoreBoard::closeButton()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();


		// Rank button
		close = Sprite::createWithSpriteFrame(ResourceInstance->GetUIFrame(ResourceInstance->UICloseName));
		close->setPosition(Vec2( boardSize.width/2 + 20, boardSize.height/2 + 20));
		this->addChild(close);

		m_listener = EventListenerTouchOneByOne::create();
		m_listener->setSwallowTouches(true);
		m_listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			Vec2 p = touch->getLocation();
			cocos2d::Rect rect = this->close->getBoundingBox();

			if (this->close->getParent())
			{
				auto w_origin = this->close->getParent()->convertToWorldSpace(rect.origin);
				rect.origin = w_origin;
			}


			if (rect.containsPoint(p))
			{
				return true; // to indicate that we have consumed it.
			}

			return false; // we did not consume this event, pass thru.
		};

		m_listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			if (this->getParent())
			{

				this->getParent()->removeChild(this);
			}
		};

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_listener, 30);

	}

	void ScoreBoard::getTopData()
	{
		requestState = RequestState::Wait;

		auto request = new network::HttpRequest();
		auto url = "http://" + std::string(ResourceInstance->ServerIP) + "/" + std::string(ResourceInstance->SAPITopScore);
		request->setUrl(url);
		request->setRequestType(network::HttpRequest::Type::GET);
		request->setResponseCallback([this](network::HttpClient* sender, network::HttpResponse* response) {
		
			if (!response)
			{
				requestState = RequestState::Fail;
				this->ShowFailUI();

				return; 
			}

			auto data = response->getResponseData();

			if (data->size() == 0)
			{
				requestState = RequestState::Fail;
				this->ShowFailUI();
			}
			else
			{
				ss.clear();
				for (auto it = data->begin(); it != data->end(); ++it)
				{
					ss << (*it);
				}

				MyLog(ss.str().c_str());
				requestState = RequestState::Get;

				ShowUI();
			}

		});

		network::HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	void ScoreBoard::ShowUI()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		this->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		// show sorce
		auto image = ui::Scale9Sprite::createWithSpriteFrame(ResourceInstance->GetUIFrame(ResourceInstance->UIFieldBGPlateName));
		image->setCapInsets(Rect(20, 20, 60, 60));
		image->setContentSize(boardSize);
		this->addChild(image);

		// parse string
		int scores[5] = { 0 };
		{
			size_t pre = 0;
			size_t post = 0;
			for (int i = 0; i < 5; i++)
			{
				auto str = ss.str();
				pre = str.find(":", pre);
				post = str.find("}", post);
				auto value = MyFramework::atoi( str.substr(pre + 1 , post - pre + 1));

				if (value == 0)
				{
					break;
				}
				else
				{
					scores[i] = value;
				}

				pre++;
				post++;
			}

		}

		char buff[10];
		for (int i = 0; i < 5; i++)
		{
			auto fontConfig = ResourceInstance->PixelFutureConfig;
			fontConfig.fontSize = 28;
			snprintf(buff, sizeof(buff), "%dst", i + 1);
			auto label = Label::createWithTTF(fontConfig, buff);	
			label->setAnchorPoint(Vec2::UNIT_Y);
			label->setTextColor(Color4B::BLACK);
			label->setPosition(10, boardSize.height - i * 60 - 10);
			
			image->addChild(label);

			label = Label::createWithTTF(fontConfig, MyFramework::Convert(scores[i]));
			label->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
			label->setTextColor(Color4B::YELLOW);
			label->setPosition(boardSize.width - 10, boardSize.height - i * 60 - 10);

			image->addChild(label);

		}


		//auto bestScore = ResourceInstance->LoadFile();
		//label = Label::createWithTTF(fontConfig, bestScore);	//best sorce
		//label->setAnchorPoint(Vec2::ZERO);
		//label->setPosition(40, 50);
		//image->addChild(label);

		//fontConfig = ResourceInstance->PixelFutureConfig;
		//fontConfig.fontSize = 28;
		//label = Label::createWithTTF(fontConfig, "Score");
		//label->setAnchorPoint(Vec2::ZERO);
		//label->setTextColor(Color4B::BLACK);
		//label->setPosition(20, 200);
		//image->addChild(label);

		//label = Label::createWithTTF(fontConfig, "Best");
		//label->setAnchorPoint(Vec2::ZERO);
		//label->setTextColor(Color4B::BLACK);
		//label->setPosition(20, 100);
		//image->addChild(label);

		closeButton();

	}

	void ScoreBoard::ShowFailUI()
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		this->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		auto image = ui::Scale9Sprite::createWithSpriteFrame(ResourceInstance->GetUIFrame(ResourceInstance->UIFieldBGPlateName));
		image->setCapInsets(Rect(20, 20, 60, 60));
		image->setContentSize(boardSize);
		this->addChild(image);

		auto fontConfig = ResourceInstance->PixelFutureConfig;
		fontConfig.fontSize = 24;
		auto label = Label::createWithTTF(fontConfig, "Sorry, Server connect\nfail...");
		label->setAnchorPoint(Vec2::UNIT_Y);
		label->setTextColor(Color4B::BLACK);
		label->setPosition(15, boardSize.height - 10);
		image->addChild(label);
		
		closeButton();
	}

}

