// multi_Thread.cpp : 定义控制台应用程序的入口点。
//
/*
编写程序完成如下功能：
1）有一int型全局变量g_Flag初始值为0；
2）在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1
3）在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2
4）线程序1需要在线程2退出后才能退出
5）主线程在检测到g_Flag从1变为2，或者从2变为1的时候退出
*/

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"

int g_Flag = 0;
HANDLE g_hMutex = NULL;//改变g_Flag的信号量
HANDLE g_hMutex_main = NULL;//主程序的信号量

//线程函数
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	while (1)
	{
		WaitForSingleObject(g_hMutex_main, INFINITE);//判断主程序是否释放信号量
		WaitForSingleObject(g_hMutex, INFINITE);
		printf("this is thread1\n");
		g_Flag = 1;
		Sleep(10);
		ReleaseMutex(g_hMutex);
		ReleaseMutex(g_hMutex_main);
	}
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	while (1)
	{
		WaitForSingleObject(g_hMutex_main, INFINITE);//判断主程序是否释放信号量
		WaitForSingleObject(g_hMutex, INFINITE);
		printf("this is thread2\n");
		g_Flag = 2;
		Sleep(10);
		ReleaseMutex(g_hMutex);
		ReleaseMutex(g_hMutex_main);
	}
	return 0;
}

int main()
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	g_hMutex_main = CreateMutex(NULL, FALSE, NULL);

	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, NULL);

	while (1)
	{
		if (g_Flag == 1)
		{
			WaitForSingleObject(g_hMutex_main, INFINITE);//确保主线程在释放g_hMutex_main之前不会被打断
			if (g_Flag == 2)
			{
				printf("this is 1 to 2\n");
				TerminateThread(hThread1, 200);
				TerminateThread(hThread2, 200);
				ReleaseMutex(g_hMutex_main);
				break;
			}
		}
	}

	CloseHandle(hThread1);
	CloseHandle(hThread2);
	system("pause");
    return 0;
}

