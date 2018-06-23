#include "SkillButton.h"
#include "HelloWorldScene.h"

USING_NS_CC;

CureButton::CureButton() :
	mItemSkill(NULL),
	mMenuSkill(NULL),
	mProgressTimer(NULL),
	mCDTime(1.f)
{
}



CureButton::~CureButton()
{

}
void CureButton::setCDTime(float time){ mCDTime = time; }
float CureButton::getCDTime() const { return mCDTime; }
CureButton* CureButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name,Sprite* _player)
{
	CureButton* skillButton = new CureButton();
	if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name,_player))
	{
		
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		delete skillButton;
		skillButton = NULL;
	}

	return NULL;
}
bool CureButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name,Sprite* _player)
{
	CCAssert(stencil_file_name, "CureButton::init stencil_file_name != NULL");
	CCAssert(button_normal_name, "CureButton::init button_normal_name != NULL");
	CCAssert(button_click_name, "CureButton::init button_click_name != NULL");
	Vec2 position = _player->getPosition();
	Size size = Director::getInstance()->getVisibleSize();
	// 添加技能按钮 下层  
	mItemSkill = CCMenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(CureButton::skillClickCallBack));
	mItemSkill->setScale(0.28f);
	mItemSkill->setPosition(position.x,position.y+300.0f);
    mMenuSkill = CCMenu::create(mItemSkill, NULL);
	mMenuSkill->setScale(0.28f);
	mMenuSkill->setPosition(position.x, position.y + 300.0f);
	addChild(mMenuSkill, -100);
   
	// 添加旋转进度条精灵---半阴影 上层  
	Sprite* progressSprite = Sprite::create(stencil_file_name);
	mProgressTimer = ProgressTimer::create(progressSprite);
	 mProgressTimer->setPosition(position.x, position.y + 300.0f);
	mProgressTimer->setVisible(false);
	addChild(mProgressTimer, 10);
	mplayer = _player;
	mCDTime = cdTime;
	return true;
}
void CureButton::changedirection(Vec2 position)
{
	mItemSkill->setPosition(-0.75*position);
	mMenuSkill->setPosition(-0.75*position);
	mProgressTimer->setPosition(-0.75*position);
}
/** 技能按钮点击回调 */
void CureButton::skillClickCallBack(cocos2d::CCObject* obj)
{
	// 冷却计时，即时状态技能按钮不可点击 
	mItemSkill->setEnabled(false);
	ProgressTimer *pBloodProGress = (ProgressTimer*)mplayer->getChildByTag(20);
	float currentblood = pBloodProGress->getPercentage();
	currentblood += 10.0f;
	pBloodProGress->setPercentage(currentblood);
	Vec2 currentplace = mplayer->getPosition();
	write(player, 1, currentplace.x, currentplace.y); //发送技能消息

	mProgressTimer->setVisible(true);
	mProgressTimer->setType(kCCProgressTimerTypeRadial);
	mProgressTimer->setReverseProgress(true); // 设置进度条为逆时针  

											  //准备一个旋转360度的动画(逐渐覆盖半透模板形成冷却效果;这里进行计时冷却动画的实现和时间控制)  

											  //注意这里冷却效果是从100%到0%顺时针变化的  
	CCActionInterval* action_progress_from_to = CCProgressFromTo::create(mCDTime, 100, 0);

	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(CureButton::skillCoolDownCallBack));
	mProgressTimer->runAction(CCSequence::create(action_progress_from_to, action_callback, NULL));
}

/** 技能冷却完成回调 */
void CureButton::skillCoolDownCallBack(CCNode* node)
{
	// 进度条技能不可见  
	mProgressTimer->setVisible(false);

	// 按钮置为可用  
	mItemSkill->setEnabled(true);
}
KnifeButton::KnifeButton() :
	mItemSkill(NULL),
	mMenuSkill(NULL),
	mProgressTimer(NULL),
	mCDTime(1.f)
{
}
KnifeButton::~KnifeButton()
{

}
void KnifeButton::setCDTime(float time){ mCDTime = time; }
float KnifeButton::getCDTime() const { return mCDTime; }
KnifeButton* KnifeButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name,Sprite* _player,Sprite* _eplayer)
{
	KnifeButton* skillButton = new KnifeButton();
	if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name,_player,_eplayer))
	{
		
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		delete skillButton;
		skillButton = NULL;
	}

	return NULL;
}
bool KnifeButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name,Sprite* _player,Sprite* _eplayer)
{
	CCAssert(stencil_file_name, "KnifeButton::init stencil_file_name != NULL");
	CCAssert(button_normal_name, "KnifeButton::init button_normal_name != NULL");
	CCAssert(button_click_name, "KnifeButton::init button_click_name != NULL");
	Size size = Director::getInstance()->getVisibleSize();
	
	// 添加技能按钮 下层  
	Vec2 position = _player->getPosition();
	
	mItemSkill = CCMenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(KnifeButton::skillClickCallBack));
	mItemSkill->setScale(.75f);
	mItemSkill->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));
    mMenuSkill = CCMenu::create(mItemSkill, NULL);
	mMenuSkill->setScale(0.75f);
	mMenuSkill->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));
	addChild(mMenuSkill, -100);
    
	// 添加旋转进度条精灵---半阴影 上层  
	Sprite* progressSprite = Sprite::create(stencil_file_name);
	mProgressTimer = ProgressTimer::create(progressSprite);
	mProgressTimer->setPosition(position.x, position.y + 300.0f);
	mProgressTimer->setVisible(false);
	addChild(mProgressTimer, 10);
	mplayer = _player;
	eplayer = _eplayer;
	mCDTime = cdTime;
	return true;
}
void KnifeButton::changedirection(Vec2 position)
{
	mItemSkill->setPosition(-0.55*position);
	mMenuSkill->setPosition(-0.55*position);
	mProgressTimer->setPosition(-0.55*position);
}
/** 技能按钮点击回调 */
void KnifeButton::skillClickCallBack(cocos2d::CCObject* obj)
{
	// 冷却计时，即时状态技能按钮不可点击  
	mItemSkill->setEnabled(false);
	ProgressTimer *pBloodProGress = (ProgressTimer*)eplayer->getChildByTag(20);
	//技能效果
	if (eplayer->getPosition().distance(mplayer->getPosition()) < 400)
	{
		pBloodProGress->setPercentage(pBloodProGress->getPercentage()-40.0f);
		Vec2 currentplace = mplayer->getPosition();
		write(player, 2, currentplace.x, currentplace.y); //发送技能消息
	}
	mProgressTimer->setVisible(true);
	mProgressTimer->setType(kCCProgressTimerTypeRadial);
	mProgressTimer->setReverseProgress(true); // 设置进度条为逆时针  

											  //准备一个旋转360度的动画(逐渐覆盖半透模板形成冷却效果;这里进行计时冷却动画的实现和时间控制)  

											  //注意这里冷却效果是从100%到0%顺时针变化的  
	CCActionInterval* action_progress_from_to = CCProgressFromTo::create(mCDTime, 100, 0);

	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(CureButton::skillCoolDownCallBack));
	mProgressTimer->runAction(CCSequence::create(action_progress_from_to, action_callback, NULL));
}

/** 技能冷却完成回调 */
void KnifeButton::skillCoolDownCallBack(CCNode* node)
{
	// 进度条技能不可见  
	mProgressTimer->setVisible(false);

	// 按钮置为可用  
	mItemSkill->setEnabled(true);
}