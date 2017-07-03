// Thread_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"

#define NAME_LINE 40
//在线程中传入参数
//线程同步

//定义线程函数传入参数的结构体
typedef struct __THREAD_DATA
{
	int nMaxNum;
	char strThreadName[NAME_LINE];

	__THREAD_DATA() : nMaxNum(0)//构造函数 初始化成员变量
	{
		memset(strThreadName, 0, NAME_LINE * sizeof(char));
	}
}THREAD_DATA;

HANDLE g_hMutex = NULL; //互斥量

//线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	THREAD_DATA *pThreadData = (THREAD_DATA*)lpParameter;

	for (int i = 0; i < pThreadData->nMaxNum; i++)
	{
		//请求获得一个互斥量锁
		WaitForSingleObject(g_hMutex, INFINITE);//无限等待
		printf("%s---%3d\n", pThreadData->strThreadName, i);
		Sleep(100);
		//释放互斥量锁
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

int main()
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);

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
		//请求获得一个互斥量锁
		WaitForSingleObject(g_hMutex, INFINITE);
		printf("主线程：%3d\n\n", i);
		Sleep(100);
		//释放互斥量锁
		ReleaseMutex(g_hMutex);
	}

	system("pause");
    return 0;
}

