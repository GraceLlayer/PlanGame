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

	void run();		//导弹前进
	static void setSpeed(int speed);//设置导弹速度
	static int getSpeed();			//获取导弹速度
private:
	static const int BOMB_WIDTH;
	static const int BOMB_HEIGHT;
	static CImageList m_Images;
	//导弹运行速度
	static int m_speed;
	int m_verSpeed;
};
