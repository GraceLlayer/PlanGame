#pragma once


// CConfigDlg 对话框

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigDlg();
	void setMyPlaneSpeed(int speed);
	int getMyPlaneSpeed();
	void setBombSpeed(int speed);
	int getBombSpeed();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// 我方战机移动速度
	int m_MyPlaneSpeed;
	// 子弹运动速度
	int m_bombSpeed;
};
