
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SkillButton.h"
#include "EndScene.h"
#include "chat.hpp"
#include "Client2.h"


class HelloWorld : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _bloodchange;
	cocos2d::TMXLayer* _keyarea;
    cocos2d::Sprite *_player1;
	cocos2d::Sprite *_player2;
	cocos2d::Sprite *_playerMe;
	cocos2d::Sprite *_playerTa;
	
public:
    // there's no 'id' in cpp, so we recommend returning the class instance Vec2er
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void GameEnd(int end);
	void setPlayerPosition(cocos2d::Vec2 position);
	bool judgePlayerBloodDrop(cocos2d::Vec2 position);
	int judgeWinCondition();
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);
	virtual void getBloodbar(cocos2d::Sprite*, float );
	virtual void update(float);
	virtual void updateCustom(float dt);
	

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};
/*
class hero {
private:
	float blood;
public:
	hero(float a) {
		blood = a;
	}
	hero() {
		blood = 100.0f;
	}
	~hero()
	{

	}
	const float getblood()
	{
		return this->blood;
	}
	void bloodchange(float change)
	{
		this->blood += change;
	}
};*/
#endif // __HELLOWORLD_SCENE_H__
