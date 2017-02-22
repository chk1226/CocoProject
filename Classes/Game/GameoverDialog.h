#ifndef _GAMEOVER_DIALOG_H_
#define _GAMEOVER_DIALOG_H_

#include "cocos2d.h"
#include "Game\TitleScene.h"
namespace MyGame
{
	class GameoverDialog : public cocos2d::Node
	{
	public:
		//GameoverDialog();
		~GameoverDialog();

		virtual bool init() override;
		void Setup(int score);

		CREATE_FUNC(GameoverDialog);
	private:
		cocos2d::EventListenerTouchOneByOne* m_listener;
		cocos2d::ui::Scale9Sprite* m_titleButton;
		void checkSaveData(int current, int old);

		void returnTitleScene();


	};

	//GameoverDialog::GameoverDialog()
	//{
	//}


}

#endif