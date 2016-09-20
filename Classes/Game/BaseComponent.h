#ifndef _BASE_COMPONENT_H_
#define _BASE_COMPONENT_H_

#include "cocos2d.h"

namespace MyGame
{

//#ifndef _MY_MACROS_
//
//#define MY_COMPONENT_CREATE_FUNC(__TYPE__) \
//	static __TYPE__* create() \
//	{ \
//		__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
//		if (pRet && pRet->init()) \
//		{ \
//			pRet->autorelease(); \
//			return pRet; \
//		} \
//		else \
//		{ \
//			delete pRet; \
//			pRet = nullptr; \
//			return nullptr; \
//		} \
//	}
//
//
//
//#endif // !_MY_MACROS_

	class BaseComponent
	{
	public:
		virtual void Update(float delta) {}

		virtual ~BaseComponent() {}

	protected:
		BaseComponent(cocos2d::Node* master)
		{
			m_Master = master;
		}

		cocos2d::Node* m_Master;
	private:

	};


}






#endif