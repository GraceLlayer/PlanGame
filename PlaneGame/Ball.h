#pragma once
#include "gameobject.h"

class CBall :
	public CGameObject
{
public:
	CBall(int x,int y,int nMontion);
	CBall(const CPoint &point,int nMontion,int speed=2);
	~CBall(void);

	BOOL Draw(CDC* pDC,BOOL bPause);
	static BOOL LoadImage(UINT bmpID);
	int GetBottom();						//��ȡը���±�Եy����
	int GetLeft();							//��ȡը�����Եx����
	int GetRight();							//��ȡը���ұ�Եx����
	int GetTop();							//��ȡը���ϱ�Եy����
	CRect GetRect();
	void SetHorizontalSpeed(int speed);
	//void SetVerticalSpeed(int speed);
	//void SetHorizontalSpeed(double speed);
	//void SetVerticalSpeed(double speed);
	void SetHorMotion(int dir);
	void run();		//�ӵ��˶�
	static const int BASE_SPEED;

private:
	static const int BALL_HEIGHT;
	static CImageList m_Images;
	int    m_nMotion;			//��ֱ�˶�����
	int m_speed;				//�ӵ���ֱ�����˶��ٶ�
	int m_horizontal_speed;		//�ӵ�ˮƽ����
	//double m_speed;				//�ӵ���ֱ�����˶��ٶ�
	//double m_horizontal_speed;		//�ӵ�ˮƽ����
	int m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��

};
