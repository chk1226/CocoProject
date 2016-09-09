#include "Framework\Utility.h"


std::string MyFramework::Convert(float num)
{
	std::ostringstream buff;
	buff << num;
	return buff.str();
}
