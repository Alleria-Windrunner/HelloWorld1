
#ifndef _SKILLBUTTON_H_  
#define _SKILLBUTTON_H_  

#include <cocos2d.h>  

class CureButton : public cocos2d::CCNode
{
public:
	CureButton();
	virtual ~CureButton();
    
	/** ����һ��SkillButton����
	*/
	static CureButton* createSkillButton(float cdTime,
		const char* stencil_file_name,
		const char* button_normal_name,
		const char* button_click_name,
		cocos2d::Sprite* _player);
	//�ı�λ��
	void changedirection(cocos2d::Vec2 position);
	/** CDʱ������
	*/
	void    setCDTime(float time); 
	float   getCDTime() const; 

    
	/** ���ܰ�ť����ص� */
	virtual void    skillClickCallBack(cocos2d::CCObject* obj);

	/** ������ȴ��ϻص�*/
	virtual void    skillCoolDownCallBack(cocos2d::CCNode* node);

private:

	/** ��ʼ�� */
	virtual bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, cocos2d::Sprite* _player);

private:
	cocos2d::Sprite*            mplayer;         //��Ҿ���
	cocos2d::CCMenuItemImage*   mItemSkill;     // ���ܰ�ť  
	cocos2d::CCMenu*            mMenuSkill;     // ���ܰ�ť����menu  
	cocos2d::CCProgressTimer*   mProgressTimer; // ʱ�����������(360����ת)  
	float                       mCDTime;          // CDʱ��  
};

class KnifeButton : public cocos2d::CCNode
{
public:
	KnifeButton();
	virtual ~KnifeButton();

	/** ����һ��SkillButton����
	*/
	static KnifeButton* createSkillButton(float cdTime,
		const char* stencil_file_name,
		const char* button_normal_name,
		const char* button_click_name,
		cocos2d::Sprite* _player,
		cocos2d::Sprite* _eplayer);
	//�ı�λ��
	void changedirection(cocos2d::Vec2 position);
	/** CDʱ������
	*/
	void    setCDTime(float time);
	float   getCDTime() const;


	/** ���ܰ�ť����ص� */
	virtual void    skillClickCallBack(cocos2d::CCObject* obj);

	/** ������ȴ��ϻص�*/
	virtual void    skillCoolDownCallBack(cocos2d::CCNode* node);

private:

	/** ��ʼ�� */
	virtual bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, cocos2d::Sprite* _player, cocos2d::Sprite* _eplayer);

private:
	cocos2d::Sprite*            mplayer;         //��Ҿ���
	cocos2d::Sprite*            eplayer;         //�з�����
	cocos2d::CCMenuItemImage*   mItemSkill;     // ���ܰ�ť  
	cocos2d::CCMenu*            mMenuSkill;     // ���ܰ�ť����menu  
	cocos2d::CCProgressTimer*   mProgressTimer; // ʱ�����������(360����ת)  
	float                       mCDTime;          // CDʱ��  
};
#endif  
