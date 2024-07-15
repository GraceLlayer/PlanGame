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

	//void moveForward(int length);		//��ǰ�ƶ�

	void moveForward();					//��ǰ�ƶ�
	void horizontalShock();				//ˮƽ���������

	void setSpeed(int speed);					//�趨�ƶ��ٶ�

	int GetLeft();

	int GetRight();

	int GetTop();

	int GetBottom();

	CBall* fire();

	CBall* fire(const CPoint &pos);

	static int GetWidth();

	//void MinusLife(int minusNum);		//��������ֵ

	//int GetLife();						//��ȡ��ǰ����ֵ

	//void SetLife(int life);				//��������ֵ


	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_speed;
	int    m_nWait;//������ʱ
	unsigned long m_lastFireTime;	//���һ�η����ӵ���ʱ��
	//int m_life;				//����ֵ

};
