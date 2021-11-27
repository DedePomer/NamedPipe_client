#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#define PATH_PIPE L"\\\\.\\pipe\\MyPipe"

int main()
{
	HANDLE hPipe;
	DWORD dwMode = PIPE_READMODE_MESSAGE;
	BOOL Success;
	system("chcp 1251");
	printf("Пользователь\n");
	while (1)
	{
		hPipe = CreateFile(PATH_PIPE, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
		Success = SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);
		if (Success)
		{
			printf("соединение есть (клиент)\n");
			break;
		}
		else
		{
			printf("соединения с сервером нет (клиент)\n");
		}
		Sleep(1000);
	}
	while (1)
	{ 	
		hPipe = CreateFile(PATH_PIPE, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
		Success = SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);
		if (Success)
		{			
			LPSTR massage = calloc(200, sizeof(CHAR));
			DWORD n;
			gets(massage);
			WriteFile(hPipe, massage, 200, &n, NULL);
		}
		else
		{
			printf("сервер отключися\n");
			break;
		}
		Sleep(1000);
		


	}
	CloseHandle(hPipe);
}


