// StudentInfo.h : CStudentInfoSet ���ʵ��



// CStudentInfoSet ʵ��

// ���������� 2017��12��18��, 10:28

#include "stdafx.h"
#include "StudentInfo.h"
IMPLEMENT_DYNAMIC(CStudentInfoSet, CRecordset)

CStudentInfoSet::CStudentInfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_StudentID = 0;
	m_StudentName = L"";
	m_Math = 0;
	m_English = 0;
	m_Chinese = 0;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}

CString CStudentInfoSet::GetDefaultConnect()
{
	return _T("DSN=Student;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2010;WSID=GL-XR-JSJ0011;DATABASE=SHI;QueryLog_On=Yes;QueryLogFile=F:\\ODBC-LOG-SQLSERVER\\QUERY.LOG;StatsLog_On=Yes;StatsLogFile=F:\\ODBC-LOG-SQLSERVER\\STATS.LOG");
}

CString CStudentInfoSet::GetDefaultSQL()
{
	return _T("[dbo].[StudentInfo]");
}

void CStudentInfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Int(pFX, _T("[StudentID]"), m_StudentID);
	RFX_Text(pFX, _T("[StudentName]"), m_StudentName);
	RFX_Int(pFX, _T("[Math]"), m_Math);
	RFX_Int(pFX, _T("[English]"), m_English);
	RFX_Int(pFX, _T("[Chinese]"), m_Chinese);

}
/////////////////////////////////////////////////////////////////////////////
// CStudentInfoSet ���

#ifdef _DEBUG
void CStudentInfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStudentInfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


