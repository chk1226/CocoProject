#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
//#include "Framework\Memory.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//MyFramework::EnableCRTMemoryLeak();
    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
