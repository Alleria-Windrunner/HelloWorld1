
#ifndef __Setting_SCENE_H__
#define __Setting_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"


class Setting : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	virtual void update(float dt);
	virtual void updateCustom(float dt);

    // a selector callback
    void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);
	void menuGo();
	void menuPlayer1Callback(cocos2d::Ref* pSender);
	void menuPlayer2Callback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Setting);
private:
	int playerchoose;
	bool decide_me;
	bool decide_ta;
	cocos2d::MenuItemFont *item1;
	cocos2d::MenuItemFont *item2;
};

#endif // __Setting_SCENE_H__
