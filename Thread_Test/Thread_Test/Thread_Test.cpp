// Thread_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	for (int i = 0; i < 5; i++)
	{
		printf("���̣߳�%3d\n\n", i);
		Sleep(100);
	}
	return 0;
}

int main()
{
	HANDLE thread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	CloseHandle(thread);

	for (int i = 0; i < 5; i++)
	{
		printf("���̣߳�%3d\n\n", i);
		Sleep(100);
	}

	system("pause");
    return 0;
}

