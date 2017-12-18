
// ODBCTest.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CODBCTestApp:
// 有关此类的实现，请参阅 ODBCTest.cpp
//

class CODBCTestApp : public CWinApp
{
public:
	CODBCTestApp();
	CDatabase& GetDatabase(){return m_dataBase;} //获取CDatabse类对象
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_dataBase;						//声明CDdatabase对象
};

extern CODBCTestApp theApp;