﻿#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#define PATH_PIPE L"\\\\.\\pipe\\MyPipe"

int main()
{
	HANDLE hPipe;// залупа
	DWORD dwMode = PIPE_READMODE_MESSAGE;
	BOOL Success, flag = TRUE, SuccessR;
	LPSTR massage = calloc(200, sizeof(CHAR));
	DWORD n;

	system("chcp 1251");
	printf("Пользователь\n");	
	while (1)
	{ 	
		hPipe = CreateFile(PATH_PIPE, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);	
		Success = SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);
		if (Success)
		{	
			if (flag)
			{
				printf("Введите сообщение для сервера: \n");							
				gets(massage);
				WriteFile(hPipe, massage, 200, &n, NULL);
				flag = FALSE;
			}	
			SuccessR = ReadFile(hPipe, massage, 200, &n,NULL);
			if (SuccessR)
			{
				printf("\nОтвет: %s\n",massage);
				flag = TRUE;
				if (massage == NULL)
				{
					printf("\n");
				}
			}
		}
		else
		{
			printf("сервер отключися\n");
		}
		Sleep(1000);		
		CloseHandle(hPipe);
	}
	
}


