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

	CBomb* fireBomb();						//ָ������׷��Ŀ��

	//CBall* fireBall()					//�����ӵ�
	
	CBomb* fireFrom(const CPoint &point);//ָ��������point��λ�÷���
	
	//void MinusLife(int minusNum);		//��������ֵ

	//int GetLife();						//��ȡ��ǰ����ֵ

	//void SetLife(int life);				//��������ֵ

	int GetFireWaitTime();				//��ȡ������ʱ��
	
	void SetFireWaitTime(int nWait);	//���÷�����ʱ��

	BOOL Fired();						//�Ƿ���Կ����䵼��

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
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ



private:

	int m_speed;
	//int m_life;
	unsigned long m_lastFireTime;
};
