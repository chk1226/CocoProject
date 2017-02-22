#include "AppDelegate.h"
#include "Game\Logger.h"
#include "Game\TitleScene.h"
#include "Game\Resource.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(750, 1134);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MyFlappyBird", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("MyFlappyBird");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
#ifdef MYGAME_DEBUG
    director->setDisplayStats(true);

#endif // MYGAME_DEBUG


    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);

    auto frameSize = glview->getFrameSize();

	
	director->setContentScaleFactor(MIN(frameSize.height/designResolutionSize.height, frameSize.width/designResolutionSize.width));
	MyLog("frameSize : %f, %f", frameSize.width, frameSize.height);
	Vec2 origin = director->getVisibleOrigin();
	MyLog("orign : %f, %f", origin.x, origin.y);
	auto visibleSize = director->getVisibleSize();
	MyLog("visibleSize : %f, %f", visibleSize.width, visibleSize.height);


    register_all_packages();

	setup();

    // create a scene. it's an autorelease object
    auto scene = MyGame::TitleScene::CreateScene();

    // run
    director->runWithScene(scene);

    return true;
}


void AppDelegate::setup()
{
	MyGame::Resource::Create();
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
