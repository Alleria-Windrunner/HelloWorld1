#include "HelloWorldScene.h"

# pragma warning (disable:4819)
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
	addChild(_tileMap,0,100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint1 = group->getObject("ninja1");
	float x1 = spawnPoint1["x"].asFloat();
	float y1 = spawnPoint1["y"].asFloat();
	_player1 = Sprite::create("ninja.png");
	_player1->setPosition(Vec2(x1,y1));
	addChild(_player1, 2, 200);
	ValueMap spawnPoint2 = group->getObject("ninja2");
	float x2 = spawnPoint2["x"].asFloat();
	float y2 = spawnPoint2["y"].asFloat();
	_player2 = Sprite::create("ninja.png");
	_player2->setPosition(Vec2(x2, y2));
	addChild(_player2, 3, 300);
	//hero _playerhero(100.0f);弃用class hero
	if (player==1)  //判定玩家、。
	{
		_playerMe = _player1;
		_playerTa = _player2;
	}
    else
	{
		_playerTa = _player1;
		_playerMe = _player2;
	}
	

	setViewpointCenter(_playerMe->getPosition());
	_bloodchange = _tileMap->getLayer("bloodchange");
	_bloodchange->setVisible(false);
	_collidable = _tileMap->getLayer("collidable");
    _collidable->setVisible(false);
	_keyarea = _tileMap->getLayer("keyarea");
	_keyarea->setVisible(false);

	this->getBloodbar(_playerMe, 100.f);//增加血条
	this->getBloodbar(_playerTa, 100.f);
	setTouchEnabled(true);
	//设置为单点触摸
	CCSize s = CCDirector::getInstance()->getWinSize();
	CureButton* mCureButton = CureButton::createSkillButton(2.f, "stencil.png", "cure.png", "cure.png",_playerMe);
	mCureButton->setPosition(ccp(s.width / 2, s.height/10-105));
	addChild(mCureButton,1,25);
	KnifeButton* mKnifeButton = KnifeButton::createSkillButton(2.f, "stencil.png", "knife.png", "knife.png", _playerMe,_playerTa);
	mKnifeButton->setPosition(ccp(s.width / 2, s.height/6));
	addChild(mKnifeButton, 1, 30);//设置技能
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->schedule(schedule_selector(HelloWorld::updateCustom), 0.08f, kRepeatForever, 0);
	this->scheduleUpdate();  //调度函数
	return true;
}
void HelloWorld::update(float dt) {//调度函数 
	Vec2 currentplace1 = _playerMe->getPosition();    //判断掉血
	ProgressTimer *pBloodProGress1 = (ProgressTimer*)_playerMe->getChildByTag(20);
	float currentblood1 = pBloodProGress1->getPercentage();
	if (judgePlayerBloodDrop(currentplace1)) 
	{
		currentblood1 -= 0.1f;
	}
	else
	{
	    currentblood1+=0.2f;
	}
	
	this->setViewpointCenter(currentplace1);          //玩家置中
	Vec2 currentplace2 = _playerTa->getPosition();
	ProgressTimer *pBloodProGress2 = (ProgressTimer*)_playerTa->getChildByTag(20);
	float currentblood2 = pBloodProGress2->getPercentage();
	if (judgePlayerBloodDrop(currentplace2))
	{
		currentblood2 -= 0.1f;
	}
	else
	{
		currentblood2 += 0.2f;
	}
	if (a1 != 0) //有消息传入
	{
		if (a1 != player) //非自己消息
		{
			if (b1 == 0);
			else if (b1 == 1) //治疗
			{
				currentblood2 += 10.0f;
			}
			else if(b1==2)   //伤害
			{
				currentblood1 -= 40.0f;
			}
			_playerTa->setPosition(a2,b2);
		}
		else if(a1==player)
		{
			a1 = 0; a2 = 0; b1 = 0; b2 = 0;
		}
		a1 = 0;
	}
	pBloodProGress1->setPercentage(currentblood1);
	pBloodProGress2->setPercentage(currentblood2);
}
void HelloWorld::updateCustom(float dt)
{
	Vec2 currentplace = _playerMe->getPosition();   //发送当前位置
	write(player,0,currentplace.x,currentplace.y);   //（玩家，技能，x，y）
	int win = judgeWinCondition();//判断胜利
	if (win != 0)
	{
		if (win == 1) GameEnd(1);
		if (win == 2) GameEnd(2);
	}
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
	//获得在OpenGL坐标
	Vec2 touchLocation = touch->getLocation();
	//转换为当前层的模型坐标系
	touchLocation = this->convertToNodeSpace(touchLocation);

	Vec2 playerPos = _playerMe->getPosition();
	Vec2 diff = touchLocation - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width;
			_playerMe->runAction(FlipX::create(false));
		} else {
			playerPos.x -= _tileMap->getTileSize().width;
			_playerMe->runAction(FlipX::create(true));
		}
	} else {
		if (diff.y > 0) {
			playerPos.y += _tileMap->getTileSize().height;
		} else {
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}
	//this->setPlayerPosition(playerPos);只移动一格
	this->setPlayerPosition(touchLocation);
}
bool HelloWorld::judgePlayerBloodDrop(cocos2d::Vec2 position)//判断玩家地图增减血量 
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _bloodchange->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string dropable = propValueMap["dropable"].asString();

		if (dropable == "true") { //掉血区域
			return true;
		}
		else if (dropable == "false") {
			return false;
		}
	}
}
void HelloWorld::setPlayerPosition(Vec2 position)
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoordTo =  this->tileCoordFromPosition(position);
	Vec2 tileCoordFrom = this->tileCoordFromPosition(_playerMe->getPosition());
	double tileCoordx = tileCoordTo.x - tileCoordFrom.x;
	double tileCoordy = tileCoordTo.y - tileCoordFrom.y;
	Vec2 tileCoord = tileCoordFrom;
	//获得瓦片的GID
	int tileGid = 0; Value prop; ValueMap propValueMap; std::string collision;
	for (int i = 0; i <= 20; i++) {
		tileGid = _collidable->getTileGIDAt(tileCoord);
		if (tileGid > 0) {
			prop = _tileMap->getPropertiesForGID(tileGid);
			propValueMap = prop.asValueMap();
			collision = propValueMap["Collidable"].asString();

			if (collision == "true") { //碰撞检测成功
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
				return;
			}
		}
		tileCoord.x += tileCoordx/20; tileCoord.y += tileCoordy/20;
	}
	//移动精灵
	//_player->setPosition(position);
	double moveX = position.x - _playerMe->getPosition().x;
	double moveY = position.y - _playerMe->getPosition().y;
	double move = sqrt(moveX*moveX + moveY*moveY);
	_playerMe->cocos2d::Node::stopAllActions();
	_playerMe->runAction(MoveTo::create(move/100, position));
	//滚动地图
	this->setViewpointCenter(_playerMe->getPosition());
}

Vec2 HelloWorld::tileCoordFromPosition(Vec2 pos) 
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x,y);
}
int HelloWorld::judgeWinCondition()
{
	//血量归零
	ProgressTimer* blood1 = (ProgressTimer*)_player1->getChildByTag(20);
	ProgressTimer* blood2 = (ProgressTimer*)_player2->getChildByTag(20);
	Vec2 position1 = _player1->getPosition();
	Vec2 position2 = _player2->getPosition();
	Vec2 tileCoord = this->tileCoordFromPosition(position1);
	int tileGid = _keyarea->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string key = propValueMap["key"].asString();
		if (key == "1") { //玩家1达到禁区
			return 1;
		}
	}
	tileCoord = this->tileCoordFromPosition(position2);
	tileGid = _keyarea->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string key = propValueMap["key"].asString();
		if (key == "2") { //玩家2达到禁区
			return 2;
		}
	}
	if (blood1->getPercentage() == 0)
	{
		return 2;
	}
	else if(blood2->getPercentage()==0)
	{
		return 1;
	}
	return 0;
}
void HelloWorld::setViewpointCenter(Vec2 position)
{
	log("setViewpointCenter");

	log("position (%f ,%f) ",position.x,position.y);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    //可以防止，视图左边超出屏幕之外。
    int x = MAX(position.x, visibleSize.width / 2);
    int y = MAX(position.y, visibleSize.height / 2);
    //可以防止，视图右边超出屏幕之外。
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
            - visibleSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
            - visibleSize.height/2);

    //屏幕中心点
    Vec2 pointA = Vec2(visibleSize.width/2, visibleSize.height/2);
	//使精灵处于屏幕中心，移动地图目标位置
    Vec2 pointB = Vec2(x, y);
	
	log("目标位置 (%f ,%f) ",pointB.x,pointB.y);

    //地图移动偏移量
    Vec2 offset =pointA - pointB;
    log("offset (%f ,%f) ",offset.x, offset.y);
    this->setPosition(offset);
	CureButton* mSkillButton1 = (CureButton*)getChildByTag(25);
	if(mSkillButton1!=NULL) mSkillButton1->CureButton::changedirection(offset);
	KnifeButton* mSkillButton2 = (KnifeButton*)getChildByTag(30);
	if (mSkillButton2 != NULL) mSkillButton2->KnifeButton::changedirection(offset);

}
void HelloWorld::getBloodbar(Sprite *guaisprite, float a){//增加角色血条
	Sprite *pBloodKongSp = Sprite::create("Bar.png");//空血条
	pBloodKongSp->setScale(0.1f);
	pBloodKongSp->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
	guaisprite->addChild(pBloodKongSp);
	Sprite *pBloodManSp = Sprite::create("BarRed.png");//满血条
	ProgressTimer *pBloodProGress = ProgressTimer::create(pBloodManSp);
	pBloodProGress->setType(kCCProgressTimerTypeBar);
	pBloodProGress->setBarChangeRate(Vec2(1, 0));
	pBloodProGress->setMidpoint(Vec2(0, 0));
	pBloodProGress->setScale(0.1f);
	pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
	pBloodProGress->setPercentage(a);
	guaisprite->addChild(pBloodProGress, 1, 20);
}
void HelloWorld::GameEnd(int end)
{
	answer = end;
	Scene * sc = End::createScene();
	Director::getInstance()->replaceScene(sc);
	
}
