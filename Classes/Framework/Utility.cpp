#include "Framework\Utility.h"


std::string MyFramework::Convert(float num)
{
	std::ostringstream buff;
	buff << num;
	return buff.str();
}

float MyFramework::Lerp(float a, float b, float f)
{
	return a + f *(b - a);
}

