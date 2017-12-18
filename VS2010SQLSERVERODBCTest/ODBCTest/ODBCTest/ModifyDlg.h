#pragma once


// CModifyDlg 对话框

class CModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyDlg)

public:
	CModifyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModifyDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_nID;
	CString m_strName;
	int m_nEnglish;
	int m_nMath;
	int m_nChinese;
	int m_nType;	//0表示添加，1表示更新
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancle();
};
