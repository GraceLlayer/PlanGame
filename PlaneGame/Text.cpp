#include "StdAfx.h"
#include "Text.h"

CText::CText(int x,int y)
{
}

CText::~CText(void)
{
}

BOOL CText::Draw(CDC* pDC,BOOL bPause)
{
	return FALSE;
}

CRect CText::GetRect()
{
	return CRect(m_ptPos,CPoint(m_ptPos.x,m_ptPos.y));
}
