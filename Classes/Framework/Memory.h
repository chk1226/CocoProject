#ifndef _MEMORY_H_
#define _MEMORY_H_

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>

#ifdef _DEBUG 
#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif 
#endif  // _DEBUG


//void* operator new (std::size_t count)
//{
//	std::cout << "custom new: " << count << std::endl;
//	if (count == 0)
//	{
//		return NULL;
//	}
//
//	return malloc(count);
//}
//
//
//void operator delete (void* ptr)
//{
//	std::cout << "custom delete" << std::endl;
//	if (ptr)
//	{
//		free(ptr);
//	}
//}
namespace MyFramework
{

	void EnableCRTMemoryLeak()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

}

#endif