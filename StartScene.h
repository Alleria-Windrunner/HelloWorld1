

#ifndef __STARTSCENE_SCENE_H__
#define __STARTSCENE_SCENE_H__

#include "cocos2d.h"
#include "SettingScene.h"

class StartScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onEnterTransitionDidFinsh(cocos2d::Ref* pSender);

	virtual void cleanup();
    
    // a selector callback
    void menuItem1Callback(cocos2d::Ref* pSender);
    void menuItem2Callback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __STARTSCENE_SCENE_H__
