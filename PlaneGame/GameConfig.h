#pragma once


// CGameConfig 对话框

class CGameConfig : public CDialog
{
	DECLARE_DYNAMIC(CGameConfig)

public:
	CGameConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void setMyPlaneSpeed(int speed);
	void setMyBombSpeed(int speed);
	void setBombWait(int nWait);
	void setGnerateEnemyPlaneWait(int nWait);
	void setEnemyPlaneFireWait(int nWait);
	void setEnemyPlaneBaseSpeed(int speed);
	void setEnemyBallBaseSpeed(int speed);
	int getMyPlaneSpeed();
	int getMyBombSpeed();
	int getBombWait();
	int getGnerateEnemyPlaneWait();
	int getEnemyPlaneFireWait();
	int getEnemyPlaneBaseSpeed();
	int getEnemyBallBaseSpeed();
private:
	// 战机移动速度
	int myPlaneSpeed;
	// 战机导弹运行速度
	int myBombSpeed;

	// 战机导弹发射时间间隔
	int bombWait;
	// 敌机产生间隔时间
	int gnerateEnemyPlaneWait;
	// 敌机子弹发射间隔时间
	int enemyPlaneFireWait;
	// 敌机基础移动速度
	int enemyPlaneBaseSpeed;
	// 敌机子弹基础速度
	int enemyBallBaseSpeed;
//public:
	
};
