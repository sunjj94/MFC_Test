
// ģ�����������������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cģ�����������������App: 
// �йش����ʵ�֣������ ģ�����������������.cpp
//

class Cģ�����������������App : public CWinApp
{
public:
	Cģ�����������������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cģ�����������������App theApp;