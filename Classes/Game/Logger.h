#ifndef _LOGGER_H_
#define _LOGGER_H_
#include "cocos2d.h"



#ifndef MYGAME_BEBUG
#define MYGAME_BEBUG

#define MyLog(format, ...) cocos2d::log(format, ##__VA_ARGS__)
#endif // !MY_BEBUG



namespace MyGame
{


}

#endif