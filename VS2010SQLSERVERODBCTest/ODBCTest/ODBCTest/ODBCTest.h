
// ODBCTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CODBCTestApp:
// �йش����ʵ�֣������ ODBCTest.cpp
//

class CODBCTestApp : public CWinApp
{
public:
	CODBCTestApp();
	CDatabase& GetDatabase(){return m_dataBase;} //��ȡCDatabse�����
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_dataBase;						//����CDdatabase����
};

extern CODBCTestApp theApp;