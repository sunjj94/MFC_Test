// Thread_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"

#define NAME_LINE 40
//���߳��д������
//�߳�ͬ��

//�����̺߳�����������Ľṹ��
typedef struct __THREAD_DATA
{
	int nMaxNum;
	char strThreadName[NAME_LINE];

	__THREAD_DATA() : nMaxNum(0)//���캯�� ��ʼ����Ա����
	{
		memset(strThreadName, 0, NAME_LINE * sizeof(char));
	}
}THREAD_DATA;

HANDLE g_hMutex = NULL; //������

//�̺߳���
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	THREAD_DATA *pThreadData = (THREAD_DATA*)lpParameter;

	for (int i = 0; i < pThreadData->nMaxNum; i++)
	{
		//������һ����������
		WaitForSingleObject(g_hMutex, INFINITE);//���޵ȴ�
		printf("%s---%3d\n", pThreadData->strThreadName, i);
		Sleep(100);
		//�ͷŻ�������
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

int main()
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	THREAD_DATA threadData1, threadData2;
	threadData1.nMaxNum = 5;
	strcpy_s(threadData1.strThreadName, "�߳�1");
	threadData2.nMaxNum = 10;
	strcpy_s(threadData2.strThreadName, "�߳�2");

	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc, &threadData1, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc, &threadData2, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	for (int i = 0; i < 5; i++)
	{
		//������һ����������
		WaitForSingleObject(g_hMutex, INFINITE);
		printf("���̣߳�%3d\n\n", i);
		Sleep(100);
		//�ͷŻ�������
		ReleaseMutex(g_hMutex);
	}

	system("pause");
    return 0;
}

