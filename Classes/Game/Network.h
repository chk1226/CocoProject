#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "cocos2d.h"

namespace MyGame
{
	enum class RequestState
	{
		Idle,
		Wait,
		Get,
		Fail
	};
	
	//struct Network
	//{
	//	//~Network();

	//	static const std::string ServerIP;
	//	static const std::string SAPITopScore;
	//	static const std::string SAPISaveScore;

	//};

	//Network::Network()
	//{
	//}

	//Network::~Network()
	//{
	//}

#ifndef ServerIP
#define ServerIP "192.168.240.97:9527"
#endif 

#ifndef SAPITopScore
#define SAPITopScore "TopScore"
#endif 

#ifndef SAPISaveScore
#define SAPISaveScore "SaveScore"
#endif 

}


#endif