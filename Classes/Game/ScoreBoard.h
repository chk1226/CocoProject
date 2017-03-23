#ifndef _SCORE_BOARD_H_
#define _SCORE_BOARD_H_

#include "cocos2d.h"
#include "Game\Network.h"

namespace MyGame
{
	class ScoreBoard : public cocos2d::Node
	{
	public:
		//ScoreBoard();
		~ScoreBoard();
		virtual bool init() override;
		void ShowUI();
		void ShowFailUI();
		
		CREATE_FUNC(ScoreBoard);

	private:
		std::stringstream ss;
		RequestState requestState;
		cocos2d::EventListenerTouchOneByOne* m_listener;
		cocos2d::Sprite* close;

		void closeButton();
		void getTopData();
		void saveScoreToServer();
	};



}

#endif