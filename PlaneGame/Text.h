#pragma once
#include "gameobject.h"

class CText :
	public CGameObject
{
public:
	CText(int x,int y);
	~CText(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	CRect GetRect();

};
