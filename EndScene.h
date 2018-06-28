
#ifndef __End_SCENE_H__
#define __End_SCENE_H__

#include "cocos2d.h"
#include "StartScene.h"

class End : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual void cleanup();
    
    // a selector callback
	void onEnterTransitionDidFinsh(Ref* pSender);
	void menuAnswerCallback(Ref* pSender);
	void meunAgainCallback(Ref* pSender);
	void menuOkCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(End);
};

#endif // __End_SCENE_H__
