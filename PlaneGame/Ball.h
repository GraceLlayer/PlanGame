#pragma once
#include "gameobject.h"

class CBall :
	public CGameObject
{
public:
	CBall(int x,int y,int nMontion);
	CBall(const CPoint &point,int nMontion,int speed=2);
	~CBall(void);

	BOOL Draw(CDC* pDC,BOOL bPause);
	static BOOL LoadImage(UINT bmpID);
	int GetBottom();						//获取炸弹下边缘y坐标
	int GetLeft();							//获取炸弹左边缘x坐标
	int GetRight();							//获取炸弹右边缘x坐标
	int GetTop();							//获取炸弹上边缘y坐标
	CRect GetRect();
	void SetHorizontalSpeed(int speed);
	//void SetVerticalSpeed(int speed);
	//void SetHorizontalSpeed(double speed);
	//void SetVerticalSpeed(double speed);
	void SetHorMotion(int dir);
	void run();		//子弹运动
	static const int BASE_SPEED;

private:
	static const int BALL_HEIGHT;
	static CImageList m_Images;
	int    m_nMotion;			//垂直运动方向
	int m_speed;				//子弹垂直方向运动速度
	int m_horizontal_speed;		//子弹水平方向
	//double m_speed;				//子弹垂直方向运动速度
	//double m_horizontal_speed;		//子弹水平方向
	int m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左

};
