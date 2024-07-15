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

	//����ըת����һ״̬
	void NextState();

	//�жϱ�ը�Ƿ����
	bool IsOver();

	int GetRight();

	int GetBottom();

	//��ȡ��ը״̬�л�ʱ����
	int GetStateChangeWait();

private:
	//ը����ͼƬ�б�
	static CImageList m_Images;
	//ͼ�������Ĳ�������
	int   m_nProcess;
	//ͼ���л�ʱ����
	int m_nWait;
public:
	static const int  EXPLOSION_WIDTH = 66;

};
