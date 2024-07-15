#include "StdAfx.h"
#include "Bomb.h"

CBomb::CBomb(int x,int y)
{
	this->m_ptPos.x=x;
	this->m_ptPos.y=y;
	this->m_verSpeed=0;
}

CBomb::CBomb(const CPoint &pos)
{
	this->m_ptPos = pos;
	this->m_verSpeed=0;
}

CBomb::~CBomb(void)
{
}

BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	return this->m_Images.Draw(pDC,0,this->m_ptPos,NULL);
}

BOOL CBomb::LoadImage(UINT bmpID)
{
	return CGameObject::LoadImage(m_Images,bmpID,RGB(0,0,0),BOMB_WIDTH,BOMB_HEIGHT,ILC_COLOR24|ILC_MASK);	
}

CRect CBomb::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x+BOMB_WIDTH,m_ptPos.y+BOMB_HEIGHT));
}

const int CBomb::BOMB_WIDTH = 10;
const int CBomb::BOMB_HEIGHT = 20;

CImageList CBomb::m_Images;

void CBomb::run()
{
	m_ptPos.y-=m_speed;
	m_ptPos.x+=m_verSpeed;
	//m_ptPos.x+=6;
}

int CBomb::m_speed = 7;

void CBomb::setSpeed(int speed)
{
	m_speed = speed;
}
int CBomb::getSpeed()
{
	return m_speed;
}

int CBomb::GetLeft()
{
	return m_ptPos.x;
}

int CBomb::GetRight()
{
	return m_ptPos.x + BOMB_WIDTH;
}

int CBomb::GetTop()
{
	return m_ptPos.y;
}

int CBomb::GetBottom()
{
	return m_ptPos.y + BOMB_HEIGHT;
}

void CBomb::SetVerSpeed(int speed)
{
	m_verSpeed = speed;
}