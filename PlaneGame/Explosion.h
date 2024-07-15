#pragma once
#include "gameobject.h"

class CExplosion :
	public CGameObject
{
public:
	CExplosion(int x,int y);
	CExplosion(CPoint &pos);
	~CExplosion(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage(UINT bmpID);

	CRect GetRect();

	//将爆炸转向下一状态
	void NextState();

	//判断爆炸是否结束
	bool IsOver();

	int GetRight();

	int GetBottom();

	//获取爆炸状态切换时间间隔
	int GetStateChangeWait();

private:
	//炸弹的图片列表
	static CImageList m_Images;
	//图像索引的步进计数
	int   m_nProcess;
	//图像切换时间间隔
	int m_nWait;
public:
	static const int  EXPLOSION_WIDTH = 66;

};
