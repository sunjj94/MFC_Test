
// MultiThread_Dialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMultiThread_DialogApp: 
// �йش����ʵ�֣������ MultiThread_Dialog.cpp
//

class CMultiThread_DialogApp : public CWinApp
{
public:
	CMultiThread_DialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMultiThread_DialogApp theApp;