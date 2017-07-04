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
int num = 0;

//�̺߳���
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	THREAD_DATA *pThreadData = (THREAD_DATA*)lpParameter;

	for (int i = 0; i < pThreadData->nMaxNum; i++)
	{
		//������һ����������
		WaitForSingleObject(g_hMutex, INFINITE);//���޵ȴ�
		num++;
		printf("%s---%3d\n", pThreadData->strThreadName, num);
		Sleep(100);
		//�ͷŻ�������
		ReleaseMutex(g_hMutex);
	}
	printf("%s �������ڵ����������ô��\n", pThreadData->strThreadName);
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	THREAD_DATA *pThreadData = (THREAD_DATA*)lpParameter;

	for (int i = 0; i < pThreadData->nMaxNum; i++)
	{
		//������һ����������
		WaitForSingleObject(g_hMutex, INFINITE);//���޵ȴ�
		num++;
		printf("%s---%3d\n", pThreadData->strThreadName, num);
		Sleep(100);
		//�ͷŻ�������
		ReleaseMutex(g_hMutex);
	}
	printf("%s �������ڵ����������ô��\n", pThreadData->strThreadName);
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

	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, &threadData1, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, &threadData2, 0, NULL);
	
	printf("�������̣߳��Ǻ�\n\n");
	printf("���̣߳������ڴ����߳�Ŷ\n");
	printf("���̣߳������ڵȴ��߳��������\n");
	
	while (1)
	{
		if (WaitForSingleObject(hThread1, INFINITE) == WAIT_OBJECT_0)
		{
			printf("�߳�1�ѽ���\n");
		}
		if (WaitForSingleObject(hThread2, INFINITE) == WAIT_OBJECT_0)
		{
			printf("�߳�2�ѽ���\n");
			break;
		}
	}

	CloseHandle(hThread1);//ֻ�ǹر��߳̾�� ���ǹر��߳�
	CloseHandle(hThread2);

	system("pause");
    return 0;
}

