// ConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "ConfigDlg.h"


// CConfigDlg 对话框

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
	, m_MyPlaneSpeed(0)
	, m_bombSpeed(0)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_MyPlaneSpeed);
	DDV_MinMaxInt(pDX, m_MyPlaneSpeed, 1, 100);
	DDX_Text(pDX, IDC_EDIT2, m_bombSpeed);
	DDV_MinMaxInt(pDX, m_bombSpeed, 1, 100);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
END_MESSAGE_MAP()


// CConfigDlg 消息处理程序

void CConfigDlg::setBombSpeed(int speed)
{
	this->m_bombSpeed = speed;
}

void CConfigDlg::setMyPlaneSpeed(int speed)
{
	this->m_MyPlaneSpeed = speed;
}

int CConfigDlg::getMyPlaneSpeed()
{
	return this->m_MyPlaneSpeed;
}

int CConfigDlg::getBombSpeed()
{
	return this->m_bombSpeed;
}