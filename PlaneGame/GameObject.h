#pragma once
#include "afx.h"

class CGameObject :
	public CObject
{

public:

	CGameObject(int x=0,int y=0);
	virtual ~CGameObject();
	
	//���ƶ���
	virtual BOOL Draw(CDC* pDC,BOOL bPause)=0;

	//��þ�������
	virtual CRect GetRect()=0;

	//������Ͻ�����
	CPoint GetPoint();

	//������Ե����
	virtual int GetLeft();	

	//����ұ�Ե����
	virtual int GetRight()=0;

	//����ϱ�Ե����
	virtual int GetTop();

	//����±�Ե����
	virtual int GetBottom()=0;

	//�������Ͻ�����
	void SetPoint(int x,int y);

	void MinusLife(int minusNum);		//��������ֵ

	int GetLife();						//��ȡ��ǰ����ֵ

	void SetLife(int life);				//��������ֵ
public:
	const static int LEFT;
	const static int RIGHT;
	const static int NO_DIR;
	const static int UP;
	const static int DOWN;

protected:
	//����ͼ��
	static BOOL LoadImage(CImageList& imgList,UINT bmpID,COLORREF crMask,int cx,int cy,int nInitial);
protected:
	//�����λ��
	CPoint  m_ptPos;
	//��������ֵ
	int m_life;

};
