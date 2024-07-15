// GameConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "GameConfig.h"


// CGameConfig 对话框

IMPLEMENT_DYNAMIC(CGameConfig, CDialog)

CGameConfig::CGameConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CGameConfig::IDD, pParent)
	, myPlaneSpeed(0)
	, myBombSpeed(0)
	, bombWait(0)
	, gnerateEnemyPlaneWait(0)
	, enemyPlaneFireWait(0)
	, enemyPlaneBaseSpeed(0)
	, enemyBallBaseSpeed(0)
{

}

CGameConfig::~CGameConfig()
{
}

void CGameConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, myPlaneSpeed);
	DDV_MinMaxInt(pDX, myPlaneSpeed, 1, 50);
	DDX_Text(pDX, IDC_EDIT2, myBombSpeed);
	DDV_MinMaxInt(pDX, myBombSpeed, 1, 20);
	DDX_Text(pDX, IDC_EDIT7, bombWait);
	DDV_MinMaxInt(pDX, bombWait, 50, 3000);
	DDX_Text(pDX, IDC_EDIT3, gnerateEnemyPlaneWait);
	DDX_Text(pDX, IDC_EDIT4, enemyPlaneFireWait);
	DDV_MinMaxInt(pDX, enemyPlaneFireWait, 1000, 9000);
	DDX_Text(pDX, IDC_EDIT5, enemyPlaneBaseSpeed);
	DDV_MinMaxInt(pDX, enemyPlaneBaseSpeed, 1, 50);
	DDX_Text(pDX, IDC_EDIT6, enemyBallBaseSpeed);
	DDV_MinMaxInt(pDX, enemyBallBaseSpeed, 1, 50);
}


BEGIN_MESSAGE_MAP(CGameConfig, CDialog)
END_MESSAGE_MAP()


// CGameConfig 消息处理程序
void CGameConfig::setMyPlaneSpeed(int speed)
{
	this->myPlaneSpeed = speed;
}
void CGameConfig::setMyBombSpeed(int speed)
{
	this->myBombSpeed = speed;
}
void CGameConfig::setBombWait(int nWait)
{
	this->bombWait = nWait;
}
void CGameConfig::setGnerateEnemyPlaneWait(int nWait)
{
	this->gnerateEnemyPlaneWait = nWait;
}
void CGameConfig::setEnemyPlaneFireWait(int nWait)
{
	this->enemyPlaneFireWait = nWait;
}
void CGameConfig::setEnemyPlaneBaseSpeed(int speed)
{
	this->enemyPlaneBaseSpeed = speed;
}
void CGameConfig::setEnemyBallBaseSpeed(int speed)
{
	this->enemyBallBaseSpeed = speed;
}
int CGameConfig::getMyPlaneSpeed()
{
	return this->myPlaneSpeed;
}
int CGameConfig::getMyBombSpeed()
{
	return this->myBombSpeed;
}
int CGameConfig::getBombWait()
{
	return this->bombWait;
}
int CGameConfig::getGnerateEnemyPlaneWait()
{
	return this->gnerateEnemyPlaneWait;
}
int CGameConfig::getEnemyPlaneFireWait()
{
	return this->enemyPlaneFireWait;
}
int CGameConfig::getEnemyPlaneBaseSpeed()
{
	return this->enemyPlaneBaseSpeed;
}
int CGameConfig::getEnemyBallBaseSpeed()
{
	return this->enemyBallBaseSpeed;
}