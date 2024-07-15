#pragma once
#include "gameobject.h"
#include "bomb.h"
#include "Ball.h"

class CMyPlane :
	public CGameObject
{
public:
	CMyPlane(int x=0,int y=0,int life=5);
	~CMyPlane(void);
	

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage(UINT bmpID);

	void SetHorMotion(int nMotion);

	int GetHorMotion() const;

	void SetVerMotion(int nMotion);

	int GetVerMotion() const;

	CRect GetRect();

	int GetLeft();

	int GetRight();

	int GetTop();

	int GetBottom();

	CBomb* fire();

	CBomb* fireBomb();						//指定导弹追踪目标

	//CBall* fireBall()					//发射子弹
	
	CBomb* fireFrom(const CPoint &point);//指定导弹由point点位置发出
	
	//void MinusLife(int minusNum);		//减少生命值

	//int GetLife();						//获取当前生命值

	//void SetLife(int life);				//设置生命值

	int GetFireWaitTime();				//获取发射间隔时间
	
	void SetFireWaitTime(int nWait);	//设置发射间隔时间

	BOOL Fired();						//是否可以开火发射导弹

	void moveForward(int length);
	void moveLeft(int length);
	void moveRight(int length);
	void moveBack(int length);
	void moveForward();
	void moveLeft();
	void moveRight();
	void moveBack();
	void setSpeed(int speed);
	int getSpeed();

public:
	static const int PLANE_WIDTH;//=50;
	static const int PLANE_HEIGHT;//=60;
private:
	
	static CImageList m_Images;
	int    m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
	int    m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下
	int    m_nWait;//发射延时



private:

	int m_speed;
	//int m_life;
	unsigned long m_lastFireTime;
};
