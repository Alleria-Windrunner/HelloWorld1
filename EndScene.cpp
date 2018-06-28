#include "EndScene.h"

USING_NS_CC;

Scene* End::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = End::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool End::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Final.wav");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite *bg = Sprite::create("background.png");
    
    // position the label on the center of the screen
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);
	//结果显示
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);
	//结果按钮
	MenuItemFont * MenuAnswer;
	if(answer==1)
	{ 
		log("answer=1");
	    MenuAnswer = MenuItemFont::create("Player1 Win!",
			CC_CALLBACK_1(End::menuAnswerCallback, this));
		MenuAnswer->setPosition(Director::getInstance()->convertToGL(Vec2(600, 200)));
	}
	else if(answer==2)
	{
		log("answer=2");
		MenuAnswer = MenuItemFont::create("Player2 Win!",
			CC_CALLBACK_1(End::menuAnswerCallback, this));
		MenuAnswer->setPosition(Director::getInstance()->convertToGL(Vec2(600, 200)));
	}
	MenuAnswer->setColor(ccc3(0, 0, 0));
	//再来一次按钮
	/*
	MenuItemFont * MenuAgain = MenuItemFont::create("Play Again!", 
		CC_CALLBACK_1(End::meunAgainCallback, this));
	MenuAgain->setPosition(Director::getInstance()->convertToGL(Vec2(100, 510)));
	MenuAgain->setColor(ccc3(0, 0, 0));
	*/
    //Ok按钮
	auto okMenuItem  = MenuItemImage::create( 
                             "ok-down.png",
                             "ok-up.png",
							 CC_CALLBACK_1(End::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(800, 510)));

    Menu* mn = Menu::create(MenuAnswer,/* MenuAgain*/okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
    this->addChild(mn);
    
    return true;
}
void End::menuAnswerCallback(Ref* pSender)
{
	
}
void End::meunAgainCallback(Ref* pSender)
{
	a1 = 0; a2 = 0; b1 = 0; b2 = 0; player = 0;
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void End::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
void End::onEnterTransitionDidFinsh(Ref* pSender)
{
	Layer::onEnterTransitionDidFinish();
	

}
void End::cleanup()
{
	Layer::cleanup();
}

