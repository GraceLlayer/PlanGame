#include "StdAfx.h"
#include "EnemyPlane.h"

//CEnemyPlane::CEnemyPlane(int x,int y,int nMotion):CGameObject(x,y)
//{
//	this->m_nMotion = nMotion;
//	this->m_speed = 3;
//	this->m_nWait = 2000;
//	m_lastFireTime = timeGetTime();
//	m_life = 5;
//}

CEnemyPlane::CEnemyPlane(const CPoint &point,int nMotion,int nWait,int life)
{
	m_ptPos = point;
	this->m_nMotion = nMotion;
	this->m_nWait = nWait;
	m_lastFireTime = timeGetTime();
	m_life = life;
}

CEnemyPlane::CEnemyPlane(int x,int y,int nMotion,int nWait,int life):CGameObject(x,y)
{
	this->m_nMotion = nMotion;
	this->m_speed = 3;
	this->m_nWait = nWait;
	m_lastFireTime = timeGetTime();
	m_life = life;
}

//CEnemyPlane::CEnemyPlane(const CPoint &point,int nMotion)
//{
//	m_ptPos = point;
//	this->m_nMotion = nMotion;
//	this->m_nWait = 2000;
//	m_lastFireTime = timeGetTime();
//	m_life = 5;
//}

CEnemyPlane::~CEnemyPlane(void)
{
}

BOOL CEnemyPlane::Draw(CDC* pDC,BOOL bPause)
{
	if(m_nMotion == CGameObject::DOWN)
		return this->m_Images.Draw(pDC,0,this->m_ptPos,NULL);
	else
		return this->m_Images.Draw(pDC,1,this->m_ptPos,NULL);
}

const int CEnemyPlane::ENEMY_HEIGHT = 35;

CImageList CEnemyPlane::m_Images;

BOOL CEnemyPlane::LoadImage(UINT bmpID)
{
	return CGameObject::LoadImage(m_Images,bmpID,RGB(0,0,0),ENEMY_HEIGHT,ENEMY_HEIGHT,ILC_COLOR24|ILC_MASK);
}

CRect CEnemyPlane::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x+ENEMY_HEIGHT,m_ptPos.y+ENEMY_HEIGHT));
}

int CEnemyPlane::GetMontion() const
{
	return m_nMotion;
}
//是否可以开火发射子弹
BOOL CEnemyPlane::Fired()
{
	//return !(clock()%m_nWait);
	return timeGetTime() - m_nWait >= m_lastFireTime;
}

CBall* CEnemyPlane::fire()
{
	int x,y;
	x = m_ptPos.x+(GetRect().Width()/2-4);

	if(m_nMotion == CGameObject::UP)
		y = GetRect().top;
	else if(m_nMotion == CGameObject::DOWN)
		y = GetRect().bottom;

	m_lastFireTime = timeGetTime();
	return new CBall(x,y,m_nMotion);
}

CBall* CEnemyPlane::fire(const CPoint &pos)
{
	int x,y;
	x = m_ptPos.x+(GetRect().Width()/2-4);
	if(m_nMotion == CGameObject::UP)
		y = GetRect().top;
	else if(m_nMotion == CGameObject::DOWN)
		y = GetRect().bottom;
	CBall *ball = new CBall(x,y,m_nMotion);
	if(pos.x>m_ptPos.x)
		ball->SetHorMotion(CGameObject::RIGHT);
	else if(pos.x<m_ptPos.x)
		ball->SetHorMotion(CGameObject::LEFT);
	
	m_lastFireTime = timeGetTime();
	//if((y-pos.y)/m_speed!=0)
		//ball->SetHorizontalSpeed(abs((x - pos.x)/((y - pos.y)/m_speed)));
	ball->SetHorizontalSpeed(2);
	return ball;
}

void CEnemyPlane::moveForward()
{
	if(m_nMotion == CGameObject::UP)
		m_ptPos.y -= m_speed;
	else if(m_nMotion == CGameObject::DOWN)
		m_ptPos.y += m_speed;
}


void CEnemyPlane::setSpeed(int speed)
{
	this->m_speed = speed;
}

int CEnemyPlane::GetLeft()
{
	return m_ptPos.x;
}

int CEnemyPlane::GetRight()
{
	return m_ptPos.x + ENEMY_HEIGHT;
}

int CEnemyPlane::GetTop()
{
	return m_ptPos.y;
}

int CEnemyPlane::GetBottom()
{
	return m_ptPos.y + ENEMY_HEIGHT;
}

int CEnemyPlane::GetWidth()
{

	return ENEMY_HEIGHT;
}

//int CEnemyPlane::GetLife()
//{
//	return m_life;
//}
//
//void CEnemyPlane::MinusLife(int minusNum)
//{
//	m_life-=minusNum;	
//}
//void CEnemyPlane::SetLife(int life)
//{
//	m_life = life;
//}


void CEnemyPlane::horizontalShock()
{
	int randNum;
	srand(timeGetTime()); 
	randNum=rand()%3;
	if(rand()%2)
		m_ptPos.x+=randNum;
	else
		m_ptPos.x-=randNum;
}
