#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <sstream>
#include <stdarg.h>
#include "cocos2d.h"


namespace MyFramework 
{

	std::string Convert(float num);
	std::string Convert(int num);
	bool ToBool(std::string str);
	float Lerp(float a, float b, float f);

	//one-depth clone
	cocos2d::Node* CloneCCNode(cocos2d::Node* source);
	// clone single node
	cocos2d::Node* CloneSingleCCNode(cocos2d::Node* source);


	/*
	static void* LoadFile(const char * filename, bool appendNull)
	{
		FILE* f = fopen(filename, "r");
		if (!f) {
			return 0;
		}

		fseek(f, 0, SEEK_END);
		auto length = ftell(f) + appendNull;
		fseek(f, 0, SEEK_SET);

		void* buffer = malloc(length);
		fread(buffer, length, 1, f);
		fclose(f);

		if (appendNull) {
			((char*)buffer)[length - 1] = 0;
		}

		return buffer;
	}
	*/


}

#endif