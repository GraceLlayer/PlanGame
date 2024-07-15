#include "StdAfx.h"
#include "Explosion.h"

CExplosion::CExplosion(int x,int y)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
	m_nProcess = 0;
	m_nWait = 3;
}

CExplosion::CExplosion(CPoint &pos)
{
	m_ptPos = pos;
	m_nProcess = 0;
	m_nWait = 3;
}

CExplosion::~CExplosion(void)
{
}

BOOL CExplosion::Draw(CDC* pDC,BOOL bPause)
{
	if (m_nProcess<0)
	{
		return FALSE;
	}
	return this->m_Images.Draw(pDC,m_nProcess%8,this->m_ptPos,NULL);
}

BOOL CExplosion::LoadImage(UINT bmpID)
{
	return CGameObject::LoadImage(m_Images,bmpID,RGB(0,0,0),66,66,ILC_COLOR24|ILC_MASK);
}

CRect CExplosion::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x+EXPLOSION_WIDTH,m_ptPos.y+EXPLOSION_WIDTH));
}

CImageList CExplosion::m_Images;

void CExplosion::NextState()
{
	m_nProcess = ++m_nProcess;
}

bool CExplosion::IsOver()
{
	return m_nProcess>=8;
}


int CExplosion::GetRight()
{
	return m_ptPos.x + EXPLOSION_WIDTH;
}

int CExplosion::GetBottom()
{
	return m_ptPos.y + EXPLOSION_WIDTH;
}

int CExplosion::GetStateChangeWait()
{
	return m_nWait;
}