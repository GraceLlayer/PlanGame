// PlaneGameDoc.cpp : CPlaneGameDoc 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameDoc

IMPLEMENT_DYNCREATE(CPlaneGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlaneGameDoc, CDocument)
	ON_COMMAND(ID_CONFIG, &CPlaneGameDoc::OnConfig)
	ON_COMMAND(ID_32773, &CPlaneGameDoc::OnEasy)
	ON_COMMAND(ID_32774, &CPlaneGameDoc::OnNormal)
	ON_COMMAND(ID_32775, &CPlaneGameDoc::OnDifficult)
	ON_COMMAND(ID_FILE_NEW, &CPlaneGameDoc::OnNewGame)
END_MESSAGE_MAP()


// CPlaneGameDoc 构造/析构

CPlaneGameDoc::CPlaneGameDoc(): m_MyPlaneSpeed(5)
, m_bombSpeed(10)
{
	// TODO: 在此添加一次性构造代码
	CMyPlane::LoadImage(IDB_MYPLANE);
	CEnemyPlane::LoadImage(IDB_ENEMYPLANE);
	CBomb::LoadImage(IDB_BOMB);
	CBall::LoadImage(IDB_ENEMYBALL);
	CExplosion::LoadImage(IDB_EXPLOSION);
	Boss::LoadImage(IDB_BOSS1);
	//Boss::LoadImage(IDB_BOSS2);
	m_MyPlanePic.LoadBitmap(IDB_MYCMyPlane);
	//m_explosionPics.LoadBitmapW(IDB_EXPLOSION);
	//m_explosionPics.Create(66,66,ILC_COLOR4|ILC_MASK,8,8);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_EXPLOSION);
	m_explosionPics.Create(66,66,ILC_COLOR24|ILC_MASK,8,8);
	m_explosionPics.Add(&bitmap,RGB(0,0,0));
	bitmap.DeleteObject();

	//PlaySound(L"ZR2612.WAV",NULL,SND_ASYNC);

	m_enemyPlanePic.LoadBitmap(IDB_MYPLANE);


}

CPlaneGameDoc::~CPlaneGameDoc()
{
	m_MyPlanePic.DeleteObject();
	m_enemyPlanePic.DeleteObject();
	m_explosionPics.DeleteImageList();
}

BOOL CPlaneGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPlaneGameDoc 序列化

void CPlaneGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CPlaneGameDoc 诊断

#ifdef _DEBUG
void CPlaneGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlaneGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPlaneGameDoc 命令





int CPlaneGameDoc::getMyPlaneSpeed(void)
{
	return this->m_MyPlaneSpeed;
}


int CPlaneGameDoc::getBombSpeed(void)
{
	return this->m_bombSpeed;
}

CImageList* CPlaneGameDoc::getExplosionPics()
{
	return &this->m_explosionPics;
}
CObList* CPlaneGameDoc::getMyBombList()
{
	return this->planeGame.GetMyBombList();
}

CObList* CPlaneGameDoc::getEnemyBallList()
{
	return this->planeGame.GetEnemyBallList();
}

CObList* CPlaneGameDoc::getEnemyPlaneList()
{
	return this->planeGame.GetEnemyPlaneList();
}

CMyPlane& CPlaneGameDoc::getMyPlane()
{
	return *this->planeGame.GetMyPlane();
}

void CPlaneGameDoc::drawGamePic(CClientDC &dc,CRect &clientRect)
{
	planeGame.Draw(dc,clientRect);
}
void CPlaneGameDoc::OnConfig()
{

	planeGame.PauseGame();

	CMyPlane &plane = *planeGame.GetMyPlane();
	CGameConfig dlg;
	dlg.setMyPlaneSpeed(plane.getSpeed());
	dlg.setBombWait(plane.GetFireWaitTime());
	dlg.setMyBombSpeed(CBomb::getSpeed());
	dlg.setEnemyPlaneFireWait(planeGame.GetEnemyPlaneFireWait());
	dlg.setGnerateEnemyPlaneWait(planeGame.GetGenerateEnemyPlaneWait());
	dlg.setEnemyBallBaseSpeed(1);
	dlg.setEnemyPlaneBaseSpeed(1);
	dlg.DoModal();
	plane.setSpeed(dlg.getMyPlaneSpeed());
	plane.SetFireWaitTime(dlg.getBombWait());
	CBomb::setSpeed(dlg.getMyBombSpeed());
	planeGame.SetEnemyPlaneFireWait(dlg.getEnemyPlaneFireWait());
	planeGame.SetGenerateEnemyPlaneWait(dlg.getGnerateEnemyPlaneWait());
	
	planeGame.CancelPauseGame();

}

CPlaneWarGame& CPlaneGameDoc::getPlaneGame()
{
	return this->planeGame;
}
void CPlaneGameDoc::OnEasy()
{
	planeGame.SetGenerateEnemyPlaneWait(2000);
}

void CPlaneGameDoc::OnNormal()
{
	planeGame.SetGenerateEnemyPlaneWait(1000);
}

void CPlaneGameDoc::OnDifficult()
{
	planeGame.SetGenerateEnemyPlaneWait(500);
}

void CPlaneGameDoc::OnNewGame()
{
	planeGame.ReStartGame();
}
