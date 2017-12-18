
// ODBCTestDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CODBCTestDlg �Ի���




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


// CODBCTestDlg ��Ϣ�������

BOOL CODBCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_StudentInfoList.DeleteAllItems();
	m_StudentInfoList.InsertColumn(0,_T("ѧ��"));
	m_StudentInfoList.InsertColumn(1,_T("����"));
	m_StudentInfoList.InsertColumn(2,_T("Ӣ��"));
	m_StudentInfoList.InsertColumn(3,_T("��ѧ"));
	m_StudentInfoList.InsertColumn(4,_T("����"));

	m_StudentInfoList.SetColumnWidth(0,100);
	m_StudentInfoList.SetColumnWidth(1,100);
	m_StudentInfoList.SetColumnWidth(2,100);
	m_StudentInfoList.SetColumnWidth(3,100);
	m_StudentInfoList.SetColumnWidth(4,100);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CODBCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CODBCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CODBCTestDlg::ShowInfo(int nType /* = -1 */)
{
	//����һ����CStudentInfoSet����
	CStudentInfoSet* pStudentSet = new CStudentInfoSet(&theApp.GetDatabase());
	if (pStudentSet == NULL)
	{
		return;
	}
	CString strSQL;
	if (nType == -1)
	{
		//����SQL��䣬��ѯStudentInfo������������
		strSQL.Format(_T("select * from StudentInfo"));
	} 
	else
	{
		switch (nType)
		{
		case 0:
			//����SQL��䣬��ѯStudentInfo�����������ݣ�������ѧ����������
			strSQL.Format(_T("select * from StudentInfo order by StudentID ASC"));
			break;
		case 1:
			//����SQL��䣬��ѯStudentInfo�����������ݣ�������������������
			strSQL.Format(_T("select * from StudentInfo order by StudentName ASC"));
			break;
		case 2:
			//����SQL��䣬��ѯStudentInfo�����������ݣ�������Ӣ����������
			strSQL.Format(_T("select * from StudentInfo order by English ASC"));
			break;
		case 3:
			//����SQL��䣬��ѯStudentInfo�����������ݣ���������ѧ��������
			strSQL.Format(_T("select * from StudentInfo order by Math ASC"));
			break;
		case 4:
			//����SQL��䣬��ѯStudentInfo�����������ݣ�������������������
			strSQL.Format(_T("select * from StudentInfo order by Chinese ASC"));
			break;
		default:
			break;
		}
	}
	pStudentSet->Open(AFX_DB_USE_DEFAULT_TYPE, strSQL);	//ִ��
	if (pStudentSet->GetRecordCount() == 0)
	{
		delete pStudentSet;	//�ͷ��ڴ�
		return;
	}

	m_StudentInfoList.DeleteAllItems();	//�����������
	int nIndex = 0;
	while(!pStudentSet->IsEOF())
	{
		CString strValue;
		strValue.Format(_T("%d"),pStudentSet->m_StudentID);		//ѧ��
		m_StudentInfoList.InsertItem(nIndex, strValue, 0);		//��������
		m_StudentInfoList.SetItemText(nIndex,1,pStudentSet->m_StudentName);//��������
		strValue.Format(_T("%d"),pStudentSet->m_English);		//Ӣ��
		m_StudentInfoList.SetItemText(nIndex, 2, strValue);		//����Ӣ��
		strValue.Format(_T("%d"),pStudentSet->m_Math);			//��ѧ
		m_StudentInfoList.SetItemText(nIndex, 3, strValue);		//������ѧ
		strValue.Format(_T("%d"),pStudentSet->m_Chinese);		//����
		m_StudentInfoList.SetItemText(nIndex, 4, strValue);		//��������
		nIndex++;
		pStudentSet->MoveNext();								//�ƶ�����һ����¼
	}
	delete pStudentSet;											//�ͷ��ڴ�
}


void CODBCTestDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CModifyDlg AddDlg;					//����CmodifyDlg�����
	AddDlg.m_nType = 0;					//�öԻ���Ϊ��ӶԻ���
	if(AddDlg.DoModal() != IDOK)		//���ǵ���ȷ�ϰ�ť
	{
		return;
	}
	CStudentInfoSet* pStudentSet = new CStudentInfoSet(&theApp.GetDatabase());
	if(pStudentSet == NULL)
	{
		return;
	}
	CString StrSQL;
	//����SQL��䣬��ѯStudentInfo������������
	StrSQL.Format(_T("select * from StudentInfo where StudentID =%d"), AddDlg.m_nID);
	pStudentSet->Open(AFX_DB_USE_DEFAULT_TYPE, StrSQL);
	if(pStudentSet->GetRecordCount() != 0)			//�ж��Ƿ�����ظ���¼
	{
		AfxMessageBox(_T("ѧ�Ų����ظ�"));
		return;
	}
	StrSQL.Format(_T("insert into StudentInfo values(\'%d\',\'%s\',\'%d\',\'%d\',\'%d\')"), 
		AddDlg.m_nID, AddDlg.m_strName, AddDlg.m_nEnglish, AddDlg.m_nMath, AddDlg.m_nChinese);
	theApp.GetDatabase().ExecuteSQL(StrSQL);			//ִ��SQL���
	ShowInfo();
	delete pStudentSet;
}


void CODBCTestDlg::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_StudentInfoList.GetFirstSelectedItemPosition();	//��ȡѡ��λ��

	if(pos == NULL)
	{
		AfxMessageBox(_T("��ѡ��Ҫɾ������Ŀ"));
		return;
	}
	while(pos)
	{
		int nItem = m_StudentInfoList.GetNextSelectedItem(pos);				//��ȡѡ���к�
		TRACE(_T("Item %d was selected!"), nItem);
		CString strValue = m_StudentInfoList.GetItemText(nItem, 0);			//��ȡ�ַ�����Ϣ
		strValue.GetString();
		CString StrSQL;
		//����SQL���
		StrSQL.Format(_T("delete from StudentInfo where StudentID = %d"), _ttoi(strValue));
		theApp.GetDatabase().ExecuteSQL(StrSQL);							//ִ��SQL���
		m_StudentInfoList.DeleteItem(nItem);								//ɾ��ѡ����Ŀ
	}



}


void CODBCTestDlg::OnBnClickedButtonUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_StudentInfoList.GetFirstSelectedItemPosition();		//��ȡѡ��λ��
	if (pos == NULL)
	{
		AfxMessageBox(_T("��ѡ��Ҫ���µ���Ŀ��"));
		return;
	}
	int nItem = m_StudentInfoList.GetNextSelectedItem(pos);					//��ȡѡ���к�
	CModifyDlg updateDlg;													//�öԻ���Ϊ���¶Ի���
	updateDlg.m_nType = 1;									
	updateDlg.m_nID = _ttoi(m_StudentInfoList.GetItemText(nItem, 0));		//��ֵѧ��
	updateDlg.m_strName = m_StudentInfoList.GetItemText(nItem, 1);			//��ֵ����
	updateDlg.m_nEnglish = _ttoi(m_StudentInfoList.GetItemText(nItem, 2));	//��ֵӢ��
	updateDlg.m_nMath = _ttoi(m_StudentInfoList.GetItemText(nItem, 3));		//��ֵ��ѧ
	updateDlg.m_nChinese = _ttoi(m_StudentInfoList.GetItemText(nItem, 4));	//��ֵ����

	if (updateDlg.DoModal() != IDOK)
	{
		return;
	}

	CString strSQL;
	//����SQL���
	strSQL.Format(_T("update StudentInfo set StudentName ='%s', English=%d, Math=%d, Chinese=%d where StudentID= %d"), 
		updateDlg.m_strName, updateDlg.m_nEnglish, updateDlg.m_nMath, updateDlg.m_nChinese, updateDlg.m_nID);
	theApp.GetDatabase().ExecuteSQL(strSQL);
	ShowInfo();
}


void CODBCTestDlg::OnBnClickedButtonCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("������˲�ѯ��ť���߼���δʵ�֣�"));
	ShowInfo();
}


void CODBCTestDlg::OnBnClickedButtonSort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("�����������ť���߼���δʵ�֣�"));
}


void CODBCTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("�������ȷ����ť"));
}
