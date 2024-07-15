// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView()
{
	// TODO: �ڴ˴���ӹ������
	m_backgroundPic.LoadBitmap(IDB_STARTBG);
}

CPlaneGameView::~CPlaneGameView()
{
	m_backgroundPic.DeleteObject();
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������

int CPlaneGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//m_planePic.LoadBitmapW(IDB_MYPLANE);
	//m_backgroundPic.LoadBitmapW(IDB_BACKGROUND);
	SetTimer(1,0,0);	//��Ļˢ�¶�ʱ��
	//SetTimer(2,200,0);	//�ӵ�������Ϣ���ն�ʱ��
	//SetTimer(3,1000,0);	//�л�������ʱ��
	//SetTimer(4,2000,0);	//�л��ӵ����䶨ʱ��

	return 0;
}

void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	KillTimer(1);
	//KillTimer(2);
	//KillTimer(3);
	//KillTimer(4);
}
void CPlaneGameView::DrawStartUI()
{
	CRect clientRect;
	this->GetClientRect(&clientRect);
	CClientDC dc(this);
	CDC mdc,bufferDC;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc,clientRect.Width(),clientRect.Height());
	mdc.CreateCompatibleDC(NULL);
	bufferDC.CreateCompatibleDC(NULL);
	mdc.SelectObject(&bmp);
	//������ͼ
	CBitmap *oldBitmap = bufferDC.SelectObject(&m_backgroundPic);
	mdc.SetStretchBltMode(COLORONCOLOR);//��������ģʽ������ͼ��᲻����
	mdc.StretchBlt(0,0,clientRect.Width(),clientRect.Height(),&bufferDC,0,0,603,414,SRCCOPY);//����ͼ��
	mdc.StretchBlt(0,0,clientRect.Width(),clientRect.Height(),&bufferDC,0,0,603,414,SRCCOPY);//����ͼ��
	TEXTMETRIC textMetric;
	GetTextMetrics(mdc,&textMetric);//��ȡ��ǰ������Ϣ
	
	HFONT font = CreateFont(clientRect.Height()/5,clientRect.Width()/10,0,0,textMetric.tmWeight,textMetric.tmItalic,
		textMetric.tmUnderlined,textMetric.tmStruckOut,textMetric.tmCharSet,0,0,0,textMetric.tmPitchAndFamily,L"");
	HFONT oldFont = (HFONT)SelectObject(mdc,font);
	//mdc.SetTextColor(RGB(255,255,255));

	int oldMode = mdc.SetBkMode(TRANSPARENT);
	DrawText(mdc,L"�ɻ���ս",-1,clientRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	DeleteObject(font);
	font = CreateFont(clientRect.Height()/10,clientRect.Width()/20,0,0,textMetric.tmWeight,textMetric.tmItalic,
		textMetric.tmUnderlined,textMetric.tmStruckOut,textMetric.tmCharSet,0,0,0,textMetric.tmPitchAndFamily,L"");
	SelectObject(mdc,font);
	DrawText(mdc,L"��Enter����ʼ��Ϸ",-1,clientRect,DT_BOTTOM|DT_CENTER|DT_SINGLELINE);
	bufferDC.SelectObject(oldBitmap);
	SelectObject(mdc,oldFont);
	SetBkMode(mdc,oldMode);
	dc.BitBlt(0,0,clientRect.Width(),clientRect.Height(),&mdc,0,0,SRCCOPY);	//���豸DC��ͼ
	DeleteObject(font);
	mdc.DeleteDC();
	bufferDC.DeleteDC();
	
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if(GetDocument()->getPlaneGame().GetGameState() == CPlaneWarGame::BEFORE_START)
	{
		DrawStartUI();
		return;
	}
	CRect clientRect;
	CClientDC dc(this);
	this->GetClientRect(&clientRect);
	switch(nIDEvent)
	{
	case 1:
		GetDocument()->drawGamePic(dc,clientRect);
		break;
	//case 2:
	//	//if(GetDocument()->plane.isFire())
	//	addBomb();
	//	break;
	//case 3:
	//	//addPlane();
	//	//GetDocument()->getPlaneGame().randomAddEnemyPlane(clientRect);
	//	break;
	//case 4:
	//	//enemyFire();
	//	break;
	}
	CView::OnTimer(nIDEvent);
}


BOOL CPlaneGameView::PreTranslateMessage(MSG* pMsg)
{
	return CView::PreTranslateMessage(pMsg);
}


void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar==VK_RETURN)
	{
		if(GetDocument()->getPlaneGame().GetGameState()==CPlaneWarGame::BEFORE_START)
			GetDocument()->getPlaneGame().StartGame();
		else if(GetDocument()->getPlaneGame().IsPause())
			GetDocument()->getPlaneGame().CancelPauseGame();
		else
			GetDocument()->getPlaneGame().PauseGame();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
