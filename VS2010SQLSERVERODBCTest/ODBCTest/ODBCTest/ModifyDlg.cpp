// ModifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ODBCTest.h"
#include "ModifyDlg.h"
#include "afxdialogex.h"


// CModifyDlg 对话框

IMPLEMENT_DYNAMIC(CModifyDlg, CDialog)

CModifyDlg::CModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyDlg::IDD, pParent)
{

	EnableAutomation();

	m_nID = 0;
	m_strName = _T("");
	m_nEnglish = 0;
	m_nMath = 0;
	m_nChinese = 0;
}

CModifyDlg::~CModifyDlg()
{
}

void CModifyDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialog::OnFinalRelease();
}

void CModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_nID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_ENGLISH, m_nEnglish);
	DDX_Text(pDX, IDC_EDIT_MATH, m_nMath);
	DDX_Text(pDX, IDC_EDIT_CHINESE, m_nChinese);
}


BEGIN_MESSAGE_MAP(CModifyDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CModifyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCLE, &CModifyDlg::OnBnClickedCancle)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CModifyDlg, CDialog)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IModifyDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {A9B662D0-5AF8-43B3-8C20-1636DCA8FC16}
static const IID IID_IModifyDlg =
{ 0xA9B662D0, 0x5AF8, 0x43B3, { 0x8C, 0x20, 0x16, 0x36, 0xDC, 0xA8, 0xFC, 0x16 } };

BEGIN_INTERFACE_MAP(CModifyDlg, CDialog)
	INTERFACE_PART(CModifyDlg, IID_IModifyDlg, Dispatch)
END_INTERFACE_MAP()


// CModifyDlg 消息处理程序


void CModifyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_nID == 0)
	{
		AfxMessageBox(_T("学号不能为空，请重新输入！"));
	}
	else if (m_strName.IsEmpty())
	{
		AfxMessageBox(_T("姓名不能为空，请重新输入！"));
	}
	else
	{
		CDialog::OnOK();
	}
}


BOOL CModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_nType == 1)
	{
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE); //如果是更新操作不能修改学号
		SetWindowText(_T("更新数据"));					//设置对话框Title
	} 
	else
	{
		SetWindowText(_T("添加数据"));					//设置对话框Title
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CModifyDlg::OnBnClickedCancle()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
