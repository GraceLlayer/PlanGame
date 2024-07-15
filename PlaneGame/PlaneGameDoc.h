// PlaneGameDoc.h : CPlaneGameDoc 类的接口
//


#pragma once
#include "myplane.h"
#include "EnemyPlane.h"
#include "PlaneWarGame.h"
#include "Explosion.h"
#include "GameConfig.h"

class CPlaneGameDoc : public CDocument
{
protected: // 仅从序列化创建
	CPlaneGameDoc();
	DECLARE_DYNCREATE(CPlaneGameDoc)

//属性
public:
	

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CPlaneGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()


//测试
public:
	//CMyPlane plane;
	//CObList bombList;
	
	//CObList List;
	//我方战机
	CBitmap m_MyPlanePic;
	//敌方战机
	CBitmap m_enemyPlanePic;
private:
	CPlaneWarGame planeGame;
	
	// 战机速度
	int m_MyPlaneSpeed;
	// //子弹移动速度
	int m_bombSpeed;
	// 爆炸图片组
	CImageList m_explosionPics;

public:
	int getMyPlaneSpeed(void);
	int getBombSpeed(void);			//
	CImageList *getExplosionPics();	//
	CObList *getMyBombList();		//
	CObList *getEnemyBallList();	//
	CObList *getEnemyPlaneList();	//获取敌方战机列表
	CMyPlane &getMyPlane();			//获取我方战机
	void drawGamePic(CClientDC &dc,CRect &clientRect);			//重绘
	CPlaneWarGame &getPlaneGame();
	afx_msg void OnConfig();
	afx_msg void OnEasy();
	afx_msg void OnNormal();
	afx_msg void OnDifficult();
	afx_msg void OnNewGame();
};


