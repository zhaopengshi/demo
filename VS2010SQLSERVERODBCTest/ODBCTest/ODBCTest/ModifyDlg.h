#pragma once


// CModifyDlg �Ի���

class CModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyDlg)

public:
	CModifyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModifyDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	int m_nType;	//0��ʾ��ӣ�1��ʾ����
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancle();
};
