
// 模拟键盘输入和鼠标输入.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C模拟键盘输入和鼠标输入App: 
// 有关此类的实现，请参阅 模拟键盘输入和鼠标输入.cpp
//

class C模拟键盘输入和鼠标输入App : public CWinApp
{
public:
	C模拟键盘输入和鼠标输入App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C模拟键盘输入和鼠标输入App theApp;