#include "Name.h"
#include "Global.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void gxy(int x, int y) { // ��������� ������� � ������ �������
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void start() { // ��������� ��������
	gxy(MAX_X / 2 - 10, MAX_Y / 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	string s = "��������";
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < j; i++) {
			cout << s[i];
		}
		Sleep(200);
		ClearConsole();
		gxy(MAX_X / 2 - 5, MAX_Y / 2);
	}
	printf("��������");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	Sleep(1000);
	ClearConsole();
}
