#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <sstream>
#include <stdarg.h>
#include "cocos2d.h"


namespace MyFramework 
{

	std::string Convert(float num);

	float Lerp(float a, float b, float f);
}

#endif