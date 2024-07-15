#include "StdAfx.h"
#include "MyPlane.h"

//CMyPlane::CMyPlane(void)
//{
//	m_speed = 5;
//	m_nWait = 100;
//	m_life = 5;
//	m_lastFireTime = timeGetTime();
//}

CMyPlane::CMyPlane(int x,int y,int life):CGameObject(x,y)
{
	m_speed = 5;
	m_nWait = 150;
	m_life = life;
	m_lastFireTime = timeGetTime();
}

CMyPlane::~CMyPlane(void)
{
}
BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
	return this->m_Images.Draw(pDC,0,this->m_ptPos,NULL);
}

const int CMyPlane::PLANE_WIDTH=50;
const int CMyPlane::PLANE_HEIGHT=60;
CImageList CMyPlane::m_Images;

BOOL CMyPlane::LoadImage(UINT bmpID)
{
	return CGameObject::LoadImageW(m_Images,bmpID,RGB(0,0,0),PLANE_WIDTH,PLANE_HEIGHT,ILC_COLOR24|ILC_MASK);
}

void CMyPlane::SetHorMotion(int nMotion)
{
	m_nHorMotion = nMotion;
}
int CMyPlane::GetHorMotion() const
{
	return m_nHorMotion;
}

void CMyPlane::SetVerMotion(int nMotion)
{
	m_nVerMotion = nMotion;
}
int CMyPlane::GetVerMotion() const
{
	return m_nVerMotion;
}

CRect CMyPlane::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT));
}

int CMyPlane::GetFireWaitTime()
{
	return m_nWait;
}

void CMyPlane::SetFireWaitTime(int nWait)
{
	m_nWait = nWait;
}

//是否可以开火发射导弹
BOOL CMyPlane::Fired()
{
	return timeGetTime()-m_nWait>=m_lastFireTime;
}

int CMyPlane::GetLeft()
{
	return m_ptPos.x;
}

int CMyPlane::GetRight()
{
	return m_ptPos.x + PLANE_WIDTH;
}
int CMyPlane::GetTop()
{
	return m_ptPos.y;
}
int CMyPlane::GetBottom()
{
	return m_ptPos.y + PLANE_HEIGHT;
}
int CMyPlane::getSpeed()
{
	return m_speed;
}







void CMyPlane::moveBack(int length)
{
	this->m_ptPos.y+=length;
}
void CMyPlane::moveLeft(int length)
{
	this->m_ptPos.x-=length;
}
void CMyPlane::moveRight(int length)
{
	this->m_ptPos.x+=length;
}
void CMyPlane::moveForward(int length)
{
	this->m_ptPos.y-=length;
}

void CMyPlane::moveBack()
{
	this->m_ptPos.y+=m_speed;
}
void CMyPlane::moveLeft()
{
	this->m_ptPos.x-=m_speed;
}
void CMyPlane::moveRight()
{
	this->m_ptPos.x+=m_speed;
}
void CMyPlane::moveForward()
{
	this->m_ptPos.y-=m_speed;
}

CBomb* CMyPlane::fire()
{
	m_lastFireTime = timeGetTime();
	return new CBomb(this->m_ptPos.x,this->m_ptPos.y);
}

CBomb* CMyPlane::fireFrom(const CPoint &point)
{
	m_lastFireTime = timeGetTime();
	return new CBomb(point);
}
CBomb* CMyPlane::fireBomb()
{
	m_lastFireTime = timeGetTime();
	return new CBomb(m_ptPos);
}
//CBomb* CMyPlane::fireBall()
//{
//	m_lastFireTime = timeGetTime();
//	return new CBall(m_ptPos);
//}
void CMyPlane::setSpeed(int speed)
{
	m_speed = speed;
}

//int CMyPlane::GetLife()
//{
//	return m_life;
//}
//
//void CMyPlane::SetLife(int life)
//{
//	m_life = life;
//}
//
//
//void CMyPlane::MinusLife(int minusNum)
//{
//	m_life -= minusNum;
//	if (m_life<0)
//		m_life=0;
//}