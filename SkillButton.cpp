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
	// ��Ӽ��ܰ�ť �²�  
	mItemSkill = CCMenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(CureButton::skillClickCallBack));
	mItemSkill->setScale(0.28f);
	mItemSkill->setPosition(position.x,position.y+300.0f);
    mMenuSkill = CCMenu::create(mItemSkill, NULL);
	mMenuSkill->setScale(0.28f);
	mMenuSkill->setPosition(position.x, position.y + 300.0f);
	addChild(mMenuSkill, -100);
   
	// �����ת����������---����Ӱ �ϲ�  
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
/** ���ܰ�ť����ص� */
void CureButton::skillClickCallBack(cocos2d::CCObject* obj)
{
	// ��ȴ��ʱ����ʱ״̬���ܰ�ť���ɵ�� 
	mItemSkill->setEnabled(false);
	ProgressTimer *pBloodProGress = (ProgressTimer*)mplayer->getChildByTag(20);
	float currentblood = pBloodProGress->getPercentage();
	currentblood += 10.0f;
	pBloodProGress->setPercentage(currentblood);
	Vec2 currentplace = mplayer->getPosition();
	write(player, 1, currentplace.x, currentplace.y); //���ͼ�����Ϣ

	mProgressTimer->setVisible(true);
	mProgressTimer->setType(kCCProgressTimerTypeRadial);
	mProgressTimer->setReverseProgress(true); // ���ý�����Ϊ��ʱ��  

											  //׼��һ����ת360�ȵĶ���(�𽥸��ǰ�͸ģ���γ���ȴЧ��;������м�ʱ��ȴ������ʵ�ֺ�ʱ�����)  

											  //ע��������ȴЧ���Ǵ�100%��0%˳ʱ��仯��  
	CCActionInterval* action_progress_from_to = CCProgressFromTo::create(mCDTime, 100, 0);

	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(CureButton::skillCoolDownCallBack));
	mProgressTimer->runAction(CCSequence::create(action_progress_from_to, action_callback, NULL));
}

/** ������ȴ��ɻص� */
void CureButton::skillCoolDownCallBack(CCNode* node)
{
	// ���������ܲ��ɼ�  
	mProgressTimer->setVisible(false);

	// ��ť��Ϊ����  
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
	
	// ��Ӽ��ܰ�ť �²�  
	Vec2 position = _player->getPosition();
	
	mItemSkill = CCMenuItemImage::create(button_normal_name, button_click_name, this, menu_selector(KnifeButton::skillClickCallBack));
	mItemSkill->setScale(.75f);
	mItemSkill->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));
    mMenuSkill = CCMenu::create(mItemSkill, NULL);
	mMenuSkill->setScale(0.75f);
	mMenuSkill->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));
	addChild(mMenuSkill, -100);
    
	// �����ת����������---����Ӱ �ϲ�  
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
/** ���ܰ�ť����ص� */
void KnifeButton::skillClickCallBack(cocos2d::CCObject* obj)
{
	// ��ȴ��ʱ����ʱ״̬���ܰ�ť���ɵ��  
	mItemSkill->setEnabled(false);
	ProgressTimer *pBloodProGress = (ProgressTimer*)eplayer->getChildByTag(20);
	//����Ч��
	if (eplayer->getPosition().distance(mplayer->getPosition()) < 400)
	{
		pBloodProGress->setPercentage(pBloodProGress->getPercentage()-40.0f);
		Vec2 currentplace = mplayer->getPosition();
		write(player, 2, currentplace.x, currentplace.y); //���ͼ�����Ϣ
	}
	mProgressTimer->setVisible(true);
	mProgressTimer->setType(kCCProgressTimerTypeRadial);
	mProgressTimer->setReverseProgress(true); // ���ý�����Ϊ��ʱ��  

											  //׼��һ����ת360�ȵĶ���(�𽥸��ǰ�͸ģ���γ���ȴЧ��;������м�ʱ��ȴ������ʵ�ֺ�ʱ�����)  

											  //ע��������ȴЧ���Ǵ�100%��0%˳ʱ��仯��  
	CCActionInterval* action_progress_from_to = CCProgressFromTo::create(mCDTime, 100, 0);

	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(CureButton::skillCoolDownCallBack));
	mProgressTimer->runAction(CCSequence::create(action_progress_from_to, action_callback, NULL));
}

/** ������ȴ��ɻص� */
void KnifeButton::skillCoolDownCallBack(CCNode* node)
{
	// ���������ܲ��ɼ�  
	mProgressTimer->setVisible(false);

	// ��ť��Ϊ����  
	mItemSkill->setEnabled(true);
}