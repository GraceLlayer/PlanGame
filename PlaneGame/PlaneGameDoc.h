// PlaneGameDoc.h : CPlaneGameDoc ��Ľӿ�
//


#pragma once
#include "myplane.h"
#include "EnemyPlane.h"
#include "PlaneWarGame.h"
#include "Explosion.h"
#include "GameConfig.h"

class CPlaneGameDoc : public CDocument
{
protected: // �������л�����
	CPlaneGameDoc();
	DECLARE_DYNCREATE(CPlaneGameDoc)

//����
public:
	

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPlaneGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()


//����
public:
	//CMyPlane plane;
	//CObList bombList;
	
	//CObList List;
	//�ҷ�ս��
	CBitmap m_MyPlanePic;
	//�з�ս��
	CBitmap m_enemyPlanePic;
private:
	CPlaneWarGame planeGame;
	
	// ս���ٶ�
	int m_MyPlaneSpeed;
	// //�ӵ��ƶ��ٶ�
	int m_bombSpeed;
	// ��ըͼƬ��
	CImageList m_explosionPics;

public:
	int getMyPlaneSpeed(void);
	int getBombSpeed(void);			//
	CImageList *getExplosionPics();	//
	CObList *getMyBombList();		//
	CObList *getEnemyBallList();	//
	CObList *getEnemyPlaneList();	//��ȡ�з�ս���б�
	CMyPlane &getMyPlane();			//��ȡ�ҷ�ս��
	void drawGamePic(CClientDC &dc,CRect &clientRect);			//�ػ�
	CPlaneWarGame &getPlaneGame();
	afx_msg void OnConfig();
	afx_msg void OnEasy();
	afx_msg void OnNormal();
	afx_msg void OnDifficult();
	afx_msg void OnNewGame();
};


