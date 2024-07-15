#pragma once


// CGameConfig �Ի���

class CGameConfig : public CDialog
{
	DECLARE_DYNAMIC(CGameConfig)

public:
	CGameConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ս���ƶ��ٶ�
	int myPlaneSpeed;
	// ս�����������ٶ�
	int myBombSpeed;

	// ս����������ʱ����
	int bombWait;
	// �л��������ʱ��
	int gnerateEnemyPlaneWait;
	// �л��ӵ�������ʱ��
	int enemyPlaneFireWait;
	// �л������ƶ��ٶ�
	int enemyPlaneBaseSpeed;
	// �л��ӵ������ٶ�
	int enemyBallBaseSpeed;
//public:
	
};
