
// ODBCTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ODBCTest.h"
#include "ODBCTestDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include "ModifyDlg.h"
#include "StudentInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CODBCTestDlg 对话框




CODBCTestDlg::CODBCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CODBCTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CODBCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STUDENT, m_StudentInfoList);
}

BEGIN_MESSAGE_MAP(CODBCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CODBCTestDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CODBCTestDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CODBCTestDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CODBCTestDlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_SORT, &CODBCTestDlg::OnBnClickedButtonSort)
	ON_BN_CLICKED(IDOK, &CODBCTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CODBCTestDlg 消息处理程序

BOOL CODBCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_StudentInfoList.DeleteAllItems();
	m_StudentInfoList.InsertColumn(0,_T("学号"));
	m_StudentInfoList.InsertColumn(1,_T("姓名"));
	m_StudentInfoList.InsertColumn(2,_T("英语"));
	m_StudentInfoList.InsertColumn(3,_T("数学"));
	m_StudentInfoList.InsertColumn(4,_T("语文"));

	m_StudentInfoList.SetColumnWidth(0,100);
	m_StudentInfoList.SetColumnWidth(1,100);
	m_StudentInfoList.SetColumnWidth(2,100);
	m_StudentInfoList.SetColumnWidth(3,100);
	m_StudentInfoList.SetColumnWidth(4,100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CODBCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CODBCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CODBCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CODBCTestDlg::ShowInfo(int nType /* = -1 */)
{
	//创建一个新CStudentInfoSet对象
	CStudentInfoSet* pStudentSet = new CStudentInfoSet(&theApp.GetDatabase());
	if (pStudentSet == NULL)
	{
		return;
	}
	CString strSQL;
	if (nType == -1)
	{
		//构造SQL语句，查询StudentInfo表中所有数据
		strSQL.Format(_T("select * from StudentInfo"));
	} 
	else
	{
		switch (nType)
		{
		case 0:
			//构造SQL语句，查询StudentInfo表中所有数据，并按照学号升序排列
			strSQL.Format(_T("select * from StudentInfo order by StudentID ASC"));
			break;
		case 1:
			//构造SQL语句，查询StudentInfo表中所有数据，并按照姓名升序排列
			strSQL.Format(_T("select * from StudentInfo order by StudentName ASC"));
			break;
		case 2:
			//构造SQL语句，查询StudentInfo表中所有数据，并按照英语升序排列
			strSQL.Format(_T("select * from StudentInfo order by English ASC"));
			break;
		case 3:
			//构造SQL语句，查询StudentInfo表中所有数据，并按照数学升序排列
			strSQL.Format(_T("select * from StudentInfo order by Math ASC"));
			break;
		case 4:
			//构造SQL语句，查询StudentInfo表中所有数据，并按照语文升序排列
			strSQL.Format(_T("select * from StudentInfo order by Chinese ASC"));
			break;
		default:
			break;
		}
	}
	pStudentSet->Open(AFX_DB_USE_DEFAULT_TYPE, strSQL);	//执行
	if (pStudentSet->GetRecordCount() == 0)
	{
		delete pStudentSet;	//释放内存
		return;
	}

	m_StudentInfoList.DeleteAllItems();	//清空所有数据
	int nIndex = 0;
	while(!pStudentSet->IsEOF())
	{
		CString strValue;
		strValue.Format(_T("%d"),pStudentSet->m_StudentID);		//学号
		m_StudentInfoList.InsertItem(nIndex, strValue, 0);		//插入数据
		m_StudentInfoList.SetItemText(nIndex,1,pStudentSet->m_StudentName);//设置姓名
		strValue.Format(_T("%d"),pStudentSet->m_English);		//英语
		m_StudentInfoList.SetItemText(nIndex, 2, strValue);		//设置英语
		strValue.Format(_T("%d"),pStudentSet->m_Math);			//数学
		m_StudentInfoList.SetItemText(nIndex, 3, strValue);		//设置数学
		strValue.Format(_T("%d"),pStudentSet->m_Chinese);		//语文
		m_StudentInfoList.SetItemText(nIndex, 4, strValue);		//设置语文
		nIndex++;
		pStudentSet->MoveNext();								//移动到下一条记录
	}
	delete pStudentSet;											//释放内存
}


void CODBCTestDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CModifyDlg AddDlg;					//声明CmodifyDlg类对象
	AddDlg.m_nType = 0;					//该对话框为添加对话框
	if(AddDlg.DoModal() != IDOK)		//不是氮气确认按钮
	{
		return;
	}
	CStudentInfoSet* pStudentSet = new CStudentInfoSet(&theApp.GetDatabase());
	if(pStudentSet == NULL)
	{
		return;
	}
	CString StrSQL;
	//构造SQL语句，查询StudentInfo表中所有数据
	StrSQL.Format(_T("select * from StudentInfo where StudentID =%d"), AddDlg.m_nID);
	pStudentSet->Open(AFX_DB_USE_DEFAULT_TYPE, StrSQL);
	if(pStudentSet->GetRecordCount() != 0)			//判断是否存在重复记录
	{
		AfxMessageBox(_T("学号不能重复"));
		return;
	}
	StrSQL.Format(_T("insert into StudentInfo values(\'%d\',\'%s\',\'%d\',\'%d\',\'%d\')"), 
		AddDlg.m_nID, AddDlg.m_strName, AddDlg.m_nEnglish, AddDlg.m_nMath, AddDlg.m_nChinese);
	theApp.GetDatabase().ExecuteSQL(StrSQL);			//执行SQL语句
	ShowInfo();
	delete pStudentSet;
}


void CODBCTestDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_StudentInfoList.GetFirstSelectedItemPosition();	//获取选中位置

	if(pos == NULL)
	{
		AfxMessageBox(_T("请选择要删除的项目"));
		return;
	}
	while(pos)
	{
		int nItem = m_StudentInfoList.GetNextSelectedItem(pos);				//获取选中行号
		TRACE(_T("Item %d was selected!"), nItem);
		CString strValue = m_StudentInfoList.GetItemText(nItem, 0);			//获取字符串信息
		strValue.GetString();
		CString StrSQL;
		//构建SQL语句
		StrSQL.Format(_T("delete from StudentInfo where StudentID = %d"), _ttoi(strValue));
		theApp.GetDatabase().ExecuteSQL(StrSQL);							//执行SQL语句
		m_StudentInfoList.DeleteItem(nItem);								//删除选中项目
	}



}


void CODBCTestDlg::OnBnClickedButtonUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_StudentInfoList.GetFirstSelectedItemPosition();		//获取选中位置
	if (pos == NULL)
	{
		AfxMessageBox(_T("请选择要更新的项目！"));
		return;
	}
	int nItem = m_StudentInfoList.GetNextSelectedItem(pos);					//获取选中行号
	CModifyDlg updateDlg;													//该对话框为更新对话框
	updateDlg.m_nType = 1;									
	updateDlg.m_nID = _ttoi(m_StudentInfoList.GetItemText(nItem, 0));		//赋值学号
	updateDlg.m_strName = m_StudentInfoList.GetItemText(nItem, 1);			//赋值姓名
	updateDlg.m_nEnglish = _ttoi(m_StudentInfoList.GetItemText(nItem, 2));	//赋值英语
	updateDlg.m_nMath = _ttoi(m_StudentInfoList.GetItemText(nItem, 3));		//赋值数学
	updateDlg.m_nChinese = _ttoi(m_StudentInfoList.GetItemText(nItem, 4));	//赋值语文

	if (updateDlg.DoModal() != IDOK)
	{
		return;
	}

	CString strSQL;
	//构建SQL语句
	strSQL.Format(_T("update StudentInfo set StudentName ='%s', English=%d, Math=%d, Chinese=%d where StudentID= %d"), 
		updateDlg.m_strName, updateDlg.m_nEnglish, updateDlg.m_nMath, updateDlg.m_nChinese, updateDlg.m_nID);
	theApp.GetDatabase().ExecuteSQL(strSQL);
	ShowInfo();
}


void CODBCTestDlg::OnBnClickedButtonCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("您点击了查询按钮，逻辑并未实现！"));
	ShowInfo();
}


void CODBCTestDlg::OnBnClickedButtonSort()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("您点击了排序按钮，逻辑并未实现！"));
}


void CODBCTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("您点击了确定按钮"));
}
