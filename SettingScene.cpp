#include "SettingScene.h"



USING_NS_CC;

Scene* Setting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setting::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite *bg = Sprite::create("setting.jpg");
    
    // position the label on the center of the screen
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);
	mapnum = 0;    //初始地图选项
	/*
	//音效
    auto soundOnMenuItem = MenuItemImage::create(
                             "on.png",
                             "on.png");
    auto soundOffMenuItem = MenuItemImage::create(
                             "off.png",
                             "off.png");
    
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), 
												soundOnMenuItem,
												soundOffMenuItem, 
												NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 220)));
    
    //音乐
    auto musicOnMenuItem  = MenuItemImage::create(
                             "on.png",
                             "on.png");
	auto musicOffMenuItem  = MenuItemImage::create(
                             "off.png",
                             "off.png");
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
                                                    musicOnMenuItem,
                                                    musicOffMenuItem,
                                                    NULL );
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 362)));
*/
	decide_me = false;
	decide_ta = false;
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);
    item1 = MenuItemFont::create("Player1",
		CC_CALLBACK_1(Setting::menuPlayer1Callback, this));
	item1->setColor(ccc3(0, 0, 0));
	item1->setPosition(Director::getInstance()->convertToGL(Vec2(500, 220)));
	item2 = MenuItemFont::create("Player2",
		CC_CALLBACK_1(Setting::menuPlayer2Callback, this));
	item2->setColor(ccc3(0, 0, 0));
	item2->setPosition(Director::getInstance()->convertToGL(Vec2(500, 360)));
	item3 = MenuItemFont::create("Map1",
		CC_CALLBACK_1(Setting::menuMap1Callback, this));
	item3->setColor(ccc3(0, 0, 0));
	item3->setPosition(Director::getInstance()->convertToGL(Vec2(800, 220)));
	item4 = MenuItemFont::create("Map2",
		CC_CALLBACK_1(Setting::menuMap2Callback, this));
	item4->setColor(ccc3(0, 0, 0));
	item4->setPosition(Director::getInstance()->convertToGL(Vec2(800, 360)));
    //Ok按钮
	okMenuItem  = MenuItemImage::create( 
                             "ok-down.png",
                             "ok-up.png",
							 CC_CALLBACK_1(Setting::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));

    Menu* mn = Menu::create(item1,item2,item3,item4,okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
    this->addChild(mn);
	item3->setEnabled(false);
	item4->setEnabled(false);
	okMenuItem->setEnabled(false);
	thread__();
	this->schedule(schedule_selector(Setting::updateCustom), 0.012f, kRepeatForever, 0);
	this->scheduleUpdate();
    return true;
}
void Setting::updateCustom(float dt)
{
	if (mapnum != 0)
	{
		okMenuItem->setEnabled(true);
	}
	a1 = int(a1); b1 = int(b1);
	log("%d %d", a1, b1);
	if (a1 != playerchoose && a1!=0)     //判断是否为对方发的
	{
		if (b1 == 0) //对方未确定
		{
			if (a1 == 1)
			{
				item1->setColor(ccc3(255, 0, 0));
				if (decide_me == false)
				{
					item1->setEnabled(false);
					item2->setEnabled(true);
				}
			}
			if (a1 == 2)
			{
				item2->setColor(ccc3(255, 0, 0));
				if (decide_me == false)
				{
					item2->setEnabled(false);
					item1->setEnabled(true);
				}
			}
		}
		else if (b1 == 3) //对方选第一张图
		{
			mapnum = 1;
			item3->setColor(ccc3(0, 0, 255));
			item4->setColor(ccc3(0, 0, 0));
		}
		else if(b1==4)
		{
			mapnum = 2;
			item3->setColor(ccc3(0, 0, 0));
			item4->setColor(ccc3(0, 0, 255));
		}
		else if(b1==1) //对方已确定
		{
			if (decide_me == false)   //我方未确定
			{
				if (a1 == 1)
				{
					item1->setColor(ccc3(0, 255, 0));
					item1->setEnabled(false);
					item2->setEnabled(true);
				}
				if (a1 == 2)
				{
					item2->setColor(ccc3(0, 255, 0));
					item2->setEnabled(false);
					item1->setEnabled(true);
				}
				item3->setEnabled(false);
				item4->setEnabled(false);
			}
			decide_ta = true;
		}
	}
	a1 = 0; b1 = 0;
	
}
void Setting::update(float dt)
{
	if (decide_me == true && decide_ta == true)
	{
		log("menuGo");
		menuGo();
	}
}
void Setting::menuPlayer1Callback(Ref* pSender) 
{
	playerchoose = 1;
	item1->setColor(ccc3(0,0,255));
	item2->setColor(ccc3(0, 0, 0));
	write(1.0f,0.0f);
	if(!decide_ta)
	{ 
		item3->setEnabled(true);
		item4->setEnabled(true);
	}
	log("menuPlayer1Callback");
}
void Setting::menuPlayer2Callback(Ref* pSender)
{
	playerchoose = 2;
	item1->setColor(ccc3(0, 0, 0));
	item2->setColor(ccc3(0, 0, 255));
	write(2.0f,0.0f);
	if (!decide_ta)
	{
		item3->setEnabled(true);
		item4->setEnabled(true);
	}
	log("menuPlayer2Callback");
}
void Setting::menuMap1Callback(Ref* pSender)
{
	mapnum = 1;
	item3->setColor(ccc3(0, 0, 255));
	item4->setColor(ccc3(0, 0, 0));
	write(playerchoose, 3.0f);
}
void Setting::menuMap2Callback(Ref* pSender)
{
	mapnum = 2;
	item3->setColor(ccc3(0, 0, 0));
	item4->setColor(ccc3(0, 0, 255));
	write(playerchoose, 4.0f);
}
void Setting::menuOkCallback(Ref* pSender)
{
	//Director::getInstance()->popScene();
	if (decide_ta == true)   menuGo();
	if(decide_me==false)
	{
		if (playerchoose == 1) 
		{ 
			write(1.0f,1.0f);
		    item1->setColor(ccc3(0, 255, 0));
		    item1->setEnabled(false);
		    item2->setEnabled(false);
		    decide_me = true;
		}
		if (playerchoose == 2) 
		{
			write(2.0f,1.0f);
			item2->setColor(ccc3(0, 255, 0));
			item1->setEnabled(false);
			item2->setEnabled(false);
			decide_me = true;
		}
	}
	
}
void Setting::menuGo()
{
	player = playerchoose;
	a1 = 0; a2 = 0; b1 = 0; b2 = 0;
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}

void Setting::menuSoundToggleCallback(Ref* pSender)
{

}


void Setting::menuMusicToggleCallback(Ref* pSender)
{
   
}


void Setting::onEnter()
{
	Layer::onEnter();
	log("Setting onEnter");
}

void Setting::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("Setting onEnterTransitionDidFinish");
}

void Setting::onExit()
{
	Layer::onExit();
	log("Setting onExit");
}

void Setting::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("Setting onExitTransitionDidStart");
}

void Setting::cleanup()
{
	Layer::cleanup();
	log("Setting cleanup");
}