// Thread_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "stdlib.h"

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	for (int i = 0; i < 5; i++)
	{
		printf("子线程：%3d\n\n", i);
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
		printf("主线程：%3d\n\n", i);
		Sleep(100);
	}

	system("pause");
    return 0;
}

