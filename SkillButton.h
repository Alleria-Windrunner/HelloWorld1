
#ifndef _SKILLBUTTON_H_  
#define _SKILLBUTTON_H_  

#include <cocos2d.h>  

class CureButton : public cocos2d::CCNode
{
public:
	CureButton();
	virtual ~CureButton();
    
	/** 创建一个SkillButton对象
	*/
	static CureButton* createSkillButton(float cdTime,
		const char* stencil_file_name,
		const char* button_normal_name,
		const char* button_click_name,
		cocos2d::Sprite* _player);
	//改变位置
	void changedirection(cocos2d::Vec2 position);
	/** CD时间设置
	*/
	void    setCDTime(float time); 
	float   getCDTime() const; 

    
	/** 技能按钮点击回调 */
	virtual void    skillClickCallBack(cocos2d::CCObject* obj);

	/** 技能冷却完毕回调*/
	virtual void    skillCoolDownCallBack(cocos2d::CCNode* node);

private:

	/** 初始化 */
	virtual bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, cocos2d::Sprite* _player);

private:
	cocos2d::Sprite*            mplayer;         //玩家精灵
	cocos2d::CCMenuItemImage*   mItemSkill;     // 技能按钮  
	cocos2d::CCMenu*            mMenuSkill;     // 技能按钮所在menu  
	cocos2d::CCProgressTimer*   mProgressTimer; // 时间进度条精灵(360度旋转)  
	float                       mCDTime;          // CD时间  
};

class KnifeButton : public cocos2d::CCNode
{
public:
	KnifeButton();
	virtual ~KnifeButton();

	/** 创建一个SkillButton对象
	*/
	static KnifeButton* createSkillButton(float cdTime,
		const char* stencil_file_name,
		const char* button_normal_name,
		const char* button_click_name,
		cocos2d::Sprite* _player,
		cocos2d::Sprite* _eplayer);
	//改变位置
	void changedirection(cocos2d::Vec2 position);
	/** CD时间设置
	*/
	void    setCDTime(float time);
	float   getCDTime() const;


	/** 技能按钮点击回调 */
	virtual void    skillClickCallBack(cocos2d::CCObject* obj);

	/** 技能冷却完毕回调*/
	virtual void    skillCoolDownCallBack(cocos2d::CCNode* node);

private:

	/** 初始化 */
	virtual bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, cocos2d::Sprite* _player, cocos2d::Sprite* _eplayer);

private:
	cocos2d::Sprite*            mplayer;         //玩家精灵
	cocos2d::Sprite*            eplayer;         //敌方精灵
	cocos2d::CCMenuItemImage*   mItemSkill;     // 技能按钮  
	cocos2d::CCMenu*            mMenuSkill;     // 技能按钮所在menu  
	cocos2d::CCProgressTimer*   mProgressTimer; // 时间进度条精灵(360度旋转)  
	float                       mCDTime;          // CD时间  
};
#endif  
