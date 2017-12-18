
// ODBCTestDlg.h : ͷ�ļ�
//
#include <afxdb.h>
#pragma once


// CODBCTestDlg �Ի���
class CODBCTestDlg : public CDialogEx
{
// ����
public:
	CODBCTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ODBCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	void ShowInfo(int nType = -1);						//�Ƿ�����-1��ʾ������
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_StudentInfoList;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonSort();
	afx_msg void OnBnClickedOk();
};
