#pragma once
#include "gameobject.h"
#include "ball.h"

class CEnemyPlane :
	public CGameObject
{
public:
	//CEnemyPlane(int x,int y,int nMotion);
	//CEnemyPlane(const CPoint &point,int nMotion);
	CEnemyPlane(int x,int y,int nMotion,int nWait=2000,int life=2);
	CEnemyPlane(const CPoint &point,int nMotion,int nWait=2000,int life=2);
	~CEnemyPlane(void);

	virtual BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage(UINT bmpID);

	CRect GetRect();

	int GetMontion() const;

	//void moveForward(int length);		//向前移动

	void moveForward();					//向前移动
	void horizontalShock();				//水平方向随机振动

	void setSpeed(int speed);					//设定移动速度

	int GetLeft();

	int GetRight();

	int GetTop();

	int GetBottom();

	CBall* fire();

	CBall* fire(const CPoint &pos);

	static int GetWidth();

	//void MinusLife(int minusNum);		//减少生命值

	//int GetLife();						//获取当前生命值

	//void SetLife(int life);				//设置生命值


	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_speed;
	int    m_nWait;//发射延时
	unsigned long m_lastFireTime;	//最后一次发射子弹的时间
	//int m_life;				//生命值

};
