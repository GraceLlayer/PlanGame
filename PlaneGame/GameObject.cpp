#include "StdAfx.h"
#include "GameObject.h"

CGameObject::CGameObject(int x,int y):m_ptPos(x,y)
{
	m_ptPos.x=x;
	m_ptPos.y=y;
}

CGameObject::~CGameObject(void)
{
}


//获得左上角坐标
CPoint CGameObject::GetPoint()
{
	return m_ptPos;
}

//加载图像
BOOL CGameObject::LoadImage(CImageList& imgList,UINT bmpID,COLORREF crMask,int cx,int cy,int nInitial)
{
	imgList.Create(cx,cy,nInitial,1,1);
	CBitmap bitmap;
	bitmap.LoadBitmapW(bmpID);
	imgList.Add(&bitmap,crMask);
	return TRUE;
}

const int CGameObject::LEFT=-1;
const int CGameObject::RIGHT=1;
const int CGameObject::NO_DIR=0;
const int CGameObject::UP = 0;
const int CGameObject::DOWN = 1;

int CGameObject::GetLeft()
{
	return m_ptPos.x;
}

int CGameObject::GetTop()
{
	return m_ptPos.y;
}

void CGameObject::SetPoint(int x,int y)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
}

int CGameObject::GetLife()
{
	return m_life;
}

void CGameObject::SetLife(int life)
{
	m_life = life;
}

void CGameObject::MinusLife(int minusNum)
{
	m_life -= minusNum;
	if (m_life<0)
		m_life=0;
}