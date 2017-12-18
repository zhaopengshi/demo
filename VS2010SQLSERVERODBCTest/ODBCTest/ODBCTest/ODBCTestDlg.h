
// ODBCTestDlg.h : 头文件
//
#include <afxdb.h>
#pragma once


// CODBCTestDlg 对话框
class CODBCTestDlg : public CDialogEx
{
// 构造
public:
	CODBCTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ODBCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	void ShowInfo(int nType = -1);						//是否排序，-1表示不排序
	// 生成的消息映射函数
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
