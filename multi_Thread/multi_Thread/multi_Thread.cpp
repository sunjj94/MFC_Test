// multi_Thread.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
��д����������¹��ܣ�
1����һint��ȫ�ֱ���g_Flag��ʼֵΪ0��
2�������߳������߳�1����ӡ��this is thread1��������g_Flag����Ϊ1
3�������߳��������߳�2����ӡ��this is thread2��������g_Flag����Ϊ2
4���߳���1��Ҫ���߳�2�˳�������˳�
5�����߳��ڼ�⵽g_Flag��1��Ϊ2�����ߴ�2��Ϊ1��ʱ���˳�
*/

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"

int g_Flag = 0;
HANDLE g_hMutex = NULL;//�ı�g_Flag���ź���
HANDLE g_hMutex_main = NULL;//��������ź���

//�̺߳���
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	while (1)
	{
		WaitForSingleObject(g_hMutex_main, INFINITE);//�ж��������Ƿ��ͷ��ź���
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
		WaitForSingleObject(g_hMutex_main, INFINITE);//�ж��������Ƿ��ͷ��ź���
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
			WaitForSingleObject(g_hMutex_main, INFINITE);//ȷ�����߳����ͷ�g_hMutex_main֮ǰ���ᱻ���
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

