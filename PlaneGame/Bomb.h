#pragma once
#include "afx.h"
#include "gameobject.h"
#include "EnemyPlane.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y);
	CBomb(const CPoint &pos);
	~CBomb(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage(UINT bmpID);

	CRect GetRect();

	int GetLeft();

	int GetRight();

	int GetTop();

	int GetBottom();

	void SetVerSpeed(int speed);

	void run();		//����ǰ��
	static void setSpeed(int speed);//���õ����ٶ�
	static int getSpeed();			//��ȡ�����ٶ�
private:
	static const int BOMB_WIDTH;
	static const int BOMB_HEIGHT;
	static CImageList m_Images;
	//���������ٶ�
	static int m_speed;
	int m_verSpeed;
};
