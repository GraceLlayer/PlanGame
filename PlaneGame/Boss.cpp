#include "StdAfx.h"
#include "Boss.h"

Boss::Boss(int x,int y,int nWait,int life)
{
	this->m_speed = 1;
	this->m_nWait = nWait;
	m_ptPos.x = x;
	m_ptPos.y = y;
	m_life = life;
	m_lastFireTime = timeGetTime();
}

Boss::Boss(const CPoint &pos,int nWait,int life)
{
	this->m_speed = 1;
	this->m_nWait = nWait;
	m_ptPos = pos;
	m_life = life;
	m_lastFireTime = timeGetTime();
}

Boss::~Boss(void)
{
}

BOOL Boss::Draw(CDC* pDC,BOOL bPause)
{
	return this->m_Images.Draw(pDC,0,this->m_ptPos,NULL);
}


const int Boss::BOSS_HEIGHT = 124;
const int Boss::BOSS_WIDTH = 150;
//const int Boss::BOSS_HEIGHT = 274;
//const int Boss::BOSS_WIDTH = 389;

CImageList Boss::m_Images;

BOOL Boss::LoadImage(UINT bmpID)
{
	return CGameObject::LoadImage(m_Images,bmpID,RGB(0,0,0),BOSS_WIDTH,BOSS_HEIGHT,ILC_COLOR24|ILC_MASK);
}

CRect Boss::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x+BOSS_WIDTH,m_ptPos.y+BOSS_HEIGHT));
}

//是否可以开火发射子弹
BOOL Boss::Fired()
{
	//return !(clock()%m_nWait);
	return timeGetTime() - m_nWait>=m_lastFireTime;
}

CBall* Boss::fire()
{
	int x,y;
	x = m_ptPos.x+(GetRect().Width()/2-4);
	y = GetRect().bottom;
	m_lastFireTime = timeGetTime();
	return new CBall(x,y,CGameObject::DOWN);
}

CBall* Boss::fire(const CPoint &pos)
{
	int x,y;
	x = m_ptPos.x+(GetRect().Width()/2-4);

	y = GetRect().bottom;
	CBall *ball = new CBall(x,y,CGameObject::DOWN);

	if(pos.x>m_ptPos.x)
		ball->SetHorMotion(CGameObject::RIGHT);
	else if(pos.x<m_ptPos.x)
		ball->SetHorMotion(CGameObject::LEFT);

	double xd = pos.x-m_ptPos.x;
	double yd = pos.y-m_ptPos.y;

	/*double distance = sqrt(xd*xd+yd*yd)
	ball->SetHorizontalSpeed(abs((xd/distance)*CBall::BASE_SPEED);
	ball->SetVerticalSpeed(abs(yd/distance)*CBall::BASE_SPEED);*/


	m_lastFireTime = timeGetTime();
	return ball;
}

CBall* Boss::fireFrom(const CPoint &pos)
{
	m_lastFireTime = timeGetTime();
	//srand(m_lastFireTime);
	CBall *ball = new CBall(pos,CGameObject::DOWN,10+rand()%5);

	if(rand()%2)
		ball->SetHorMotion(CGameObject::LEFT);
	else
		ball->SetHorMotion(CGameObject::RIGHT);
	ball->SetHorizontalSpeed(rand()%3);
	
	return ball;
}

//CObList* Boss::fire(const CPoint &pos,int n)
//{
//	int x,y;
//	CObList list;
//	x = m_ptPos.x+(GetRect().Width()/2-4);
//	if(m_nMotion == CGameObject::UP)
//		y = GetRect().top;
//	else if(m_nMotion == CGameObject::DOWN)
//		y = GetRect().bottom;
//	CBall *ball = new CBall(x,y,m_nMotion);
//	if(pos.x>m_ptPos.x)
//		ball->SetHorMotion(CGameObject::RIGHT);
//	else if(pos.x<m_ptPos.x)
//		ball->SetHorMotion(CGameObject::LEFT);
//	list.AddTail(ball);
//	ball->SetHorizontalSpeed(3);
//	//if((y-pos.y)/m_speed!=0)
//	//ball->SetHorizontalSpeed(abs((x - pos.x)/((y - pos.y)/m_speed)));
//	for(int i=0;i<10;i++)
//	{
//		ball = new CBall(x,y,m_nMotion);
//		if(pos.x>m_ptPos.x)
//			ball->SetHorMotion(CGameObject::RIGHT);
//		else if(pos.x<m_ptPos.x)
//			ball->SetHorMotion(CGameObject::LEFT);
//		list.AddTail(ball);
//	}
//	
//	return &list;
//}


void Boss::setSpeed(int speed)
{
	this->m_speed = speed;
}

int Boss::getSpeed()
{
	return this->m_speed;
}


int Boss::GetRight()
{
	return m_ptPos.x + BOSS_WIDTH;
}

int Boss::GetBottom()
{
	return m_ptPos.y + BOSS_HEIGHT;
}

int Boss::GetWidth()
{

	return BOSS_WIDTH;
}

void Boss::moveBack()
{
	this->m_ptPos.y+=m_speed;
}
void Boss::moveLeft()
{
	this->m_ptPos.x-=m_speed;
}
void Boss::moveRight()
{
	this->m_ptPos.x+=m_speed;
}
void Boss::moveForward()
{
	this->m_ptPos.y-=m_speed;
}

//int Boss::GetLife()
//{
//	return m_life;
//}
//
//void Boss::SetLife(int life)
//{
//	m_life = life;
//}
//
//void Boss::MinusLife(int minusNum)
//{
//	m_life -= minusNum;
//	if (m_life<0)
//		m_life=0;
//}

void Boss::horizontalShock()
{
	int randNum;
	//srand(timeGetTime()); 
	randNum=rand()%(m_speed*2+1);
	if(rand()%2)
		m_ptPos.x+=randNum;
	else
		m_ptPos.x-=randNum;
}