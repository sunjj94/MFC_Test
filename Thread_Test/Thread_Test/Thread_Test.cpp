// Thread_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"

#define NAME_LINE 40
//在线程中传入参数
typedef struct __THREAD_DATA
{
	int nMaxNum;
	char strThreadName[NAME_LINE];

	__THREAD_DATA() : nMaxNum(0)//构造函数 初始化成员变量
	{
		memset(strThreadName, 0, NAME_LINE * sizeof(char));
	}
}THREAD_DATA;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	THREAD_DATA *pThreadData = (THREAD_DATA*)lpParameter;

	for (int i = 0; i < pThreadData->nMaxNum; i++)
	{
		printf("%s---%3d\n", pThreadData->strThreadName, i);
		Sleep(100);
	}
	return 0;
}

int main()
{
	THREAD_DATA threadData1, threadData2;
	threadData1.nMaxNum = 5;
	strcpy_s(threadData1.strThreadName, "线程1");
	threadData2.nMaxNum = 10;
	strcpy_s(threadData2.strThreadName, "线程2");

	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc, &threadData1, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc, &threadData2, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	for (int i = 0; i < 5; i++)
	{
		printf("主线程：%3d\n\n", i);
		Sleep(100);
	}

	system("pause");
    return 0;
}

