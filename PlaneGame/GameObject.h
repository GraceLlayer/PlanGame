#pragma once
#include "afx.h"

class CGameObject :
	public CObject
{

public:

	CGameObject(int x=0,int y=0);
	virtual ~CGameObject();
	
	//绘制对象
	virtual BOOL Draw(CDC* pDC,BOOL bPause)=0;

	//获得矩形区域
	virtual CRect GetRect()=0;

	//获得左上角坐标
	CPoint GetPoint();

	//获得左边缘坐标
	virtual int GetLeft();	

	//获得右边缘坐标
	virtual int GetRight()=0;

	//获得上边缘坐标
	virtual int GetTop();

	//获得下边缘坐标
	virtual int GetBottom()=0;

	//设置左上角坐标
	void SetPoint(int x,int y);

	void MinusLife(int minusNum);		//减少生命值

	int GetLife();						//获取当前生命值

	void SetLife(int life);				//设置生命值
public:
	const static int LEFT;
	const static int RIGHT;
	const static int NO_DIR;
	const static int UP;
	const static int DOWN;

protected:
	//加载图像
	static BOOL LoadImage(CImageList& imgList,UINT bmpID,COLORREF crMask,int cx,int cy,int nInitial);
protected:
	//物体的位置
	CPoint  m_ptPos;
	//对象生命值
	int m_life;

};
