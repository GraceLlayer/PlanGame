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

	//void moveForward(int length);		//��ǰ�ƶ�

	void moveForward();					//��ǰ�ƶ�
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

	void horizontalShock();				//ˮƽ���������
	static int GetWidth();
	////��������ֵ
	//void MinusLife(int minusNum);

	////��ȡ��ǰ����ֵ
	//int GetLife();

	////��������ֵ
	//void SetLife(int life);

	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int BOSS_HEIGHT;
	static const int BOSS_WIDTH;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����

	//�ٶ�
	int m_speed;
	int    m_nWait;//������ʱ
	int m_life;
	unsigned long m_lastFireTime;
};
