// ModifyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBCTest.h"
#include "ModifyDlg.h"
#include "afxdialogex.h"


// CModifyDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IModifyDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {A9B662D0-5AF8-43B3-8C20-1636DCA8FC16}
static const IID IID_IModifyDlg =
{ 0xA9B662D0, 0x5AF8, 0x43B3, { 0x8C, 0x20, 0x16, 0x36, 0xDC, 0xA8, 0xFC, 0x16 } };

BEGIN_INTERFACE_MAP(CModifyDlg, CDialog)
	INTERFACE_PART(CModifyDlg, IID_IModifyDlg, Dispatch)
END_INTERFACE_MAP()


// CModifyDlg ��Ϣ�������


void CModifyDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_nID == 0)
	{
		AfxMessageBox(_T("ѧ�Ų���Ϊ�գ����������룡"));
	}
	else if (m_strName.IsEmpty())
	{
		AfxMessageBox(_T("��������Ϊ�գ����������룡"));
	}
	else
	{
		CDialog::OnOK();
	}
}


BOOL CModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_nType == 1)
	{
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE); //����Ǹ��²��������޸�ѧ��
		SetWindowText(_T("��������"));					//���öԻ���Title
	} 
	else
	{
		SetWindowText(_T("�������"));					//���öԻ���Title
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CModifyDlg::OnBnClickedCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
