#pragma once
#include "GameObject.h"
#include "Ball.h"

class Boss :
	public CGameObject
{
public:
	Boss(int x,int y,int nWait = 2000,int life = 60);
	Boss(const CPoint &pos,int nWait = 2000,int life = 60);
	~Boss(void);

	BOOL Draw(CDC* pDC,BOOL bPause);
	static BOOL LoadImage(UINT bmpID);

	CRect GetRect();

	int GetMontion() const;

	//void moveForward(int length);		//向前移动

	void moveForward();					//向前移动
	int GetRight();
	int GetBottom();
	CBall* fire();
	CBall* fire(const CPoint &pos);
	CBall* fireFrom(const CPoint &pos);
	void moveLeft();
	void moveRight();
	void moveBack();
	void setSpeed(int speed);
	int getSpeed();

	void horizontalShock();				//水平方向随机振动
	static int GetWidth();
	////减少生命值
	//void MinusLife(int minusNum);

	////获取当前生命值
	//int GetLife();

	////设置生命值
	//void SetLife(int life);

	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int BOSS_HEIGHT;
	static const int BOSS_WIDTH;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上

	//速度
	int m_speed;
	int    m_nWait;//发射延时
	int m_life;
	unsigned long m_lastFireTime;
};
