#pragma once


// CConfigDlg �Ի���

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfigDlg();
	void setMyPlaneSpeed(int speed);
	int getMyPlaneSpeed();
	void setBombSpeed(int speed);
	int getBombSpeed();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// �ҷ�ս���ƶ��ٶ�
	int m_MyPlaneSpeed;
	// �ӵ��˶��ٶ�
	int m_bombSpeed;
};
