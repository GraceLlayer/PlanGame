#include "StdAfx.h"
#include "Ball.h"

CBall::CBall(int x,int y,int nMontion)
{
	this->m_ptPos.x = x;
	this->m_ptPos.y = y;
	this->m_nMotion = nMontion;
	this->m_speed = 2;
	this->m_horizontal_speed = 0;
	m_nHorMotion = 0;
}

CBall::CBall(const CPoint &point,int nMontion,int speed)
{
	this->m_ptPos = point;
	this->m_nMotion = nMontion;
	this->m_speed = speed;
	this->m_horizontal_speed = 0;
	m_nHorMotion = 0;
}

CBall::~CBall(void)
{
}

BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
	return this->m_Images.Draw(pDC,0,this->m_ptPos,NULL);
}

BOOL CBall::LoadImage(UINT bmpID)
{
	return CGameObject::LoadImage(m_Images,bmpID,RGB(0,0,0),BALL_HEIGHT,BALL_HEIGHT,ILC_COLOR24|ILC_MASK);
}

CRect CBall::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
}

void CBall::run()
{
	if(m_nMotion == CGameObject::UP)
		m_ptPos.y-=m_speed;
	else if(m_nMotion == CGameObject::DOWN)
		m_ptPos.y+=m_speed;
	if(m_nHorMotion == CGameObject::LEFT)
		m_ptPos.x-=m_horizontal_speed;
	else if(m_nHorMotion == CGameObject::RIGHT)
		m_ptPos.x+=m_horizontal_speed;
}
const int CBall::BALL_HEIGHT=8;

CImageList CBall::m_Images;

void CBall::SetHorMotion(int dir)
{
	m_nHorMotion = dir;
}

int CBall::GetBottom()
{
	return m_ptPos.y+BALL_HEIGHT;
}

int CBall::GetTop()
{
	return m_ptPos.y;
}

int CBall::GetLeft()
{
	return m_ptPos.x;
}

int CBall::GetRight()
{
	return m_ptPos.x+BALL_HEIGHT;
}

void CBall::SetHorizontalSpeed(int speed)
{
	m_horizontal_speed = speed;
}
//void CBall::SetHorizontalSpeed(double speed)
//{
//	m_horizontal_speed = speed;
//}

const int CBall::BASE_SPEED = 3;