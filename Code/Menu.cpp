#include "Menu.h"
#include "stdlib.h"
#include "windows.h"
#include "stdio.h"
#include "Name.h"
#include "Global.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

extern int p = 0;
mutex mx1;

void print_creator() {
	ClearConsole();
	gxy(27, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("110100001001000011010000101110111101000010110101110100001011101011010001100000011101000010110101110");
	gxy(19, 15);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("100001011100100100000110100001010000111010000101111001101000010111000110100001011110111010000101111101101000010110010");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_getch();
}

void print_settings() {

	int chs = 0;
	int z = true;
	vector<string> V{"Скорость врагов: ", "Игрока: "};
	while (z) {
		ofstream fl;
		ClearConsole();
		for (int i = 0; i < 2; i++) {
			gxy(55, 10 + 3 * i);
			if (i == chs) { 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << ">> "; 
			}
			cout << V[i];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			if (i == 0) { cout << SPEED_ENEMY; }
			if (i == 1) { cout << PERS; }
		}
		gxy(43, 16);
		cout << "Нажмите ctrl + S, чтобы сохранить навсегда";

		char a = _getch();

		switch (a)
		{
		case 13:
			z = false;
			break;
		case 19:
			fl.open("C:\\Users\\Alex\\Desktop\\Settings.txt");
			fl << SPEED_ENEMY << "\n";
			fl << (int)PERS << "\n";
		case 27:
			z = false;
			break;
		case 72:
			if (chs == 0) { if (SPEED_ENEMY > 1) { SPEED_ENEMY -= 1; } }
			if (chs == 1) { if (PERS > 32) { PERS -= 1; } }
			break;
		case 80:
			if (chs == 0) { if (SPEED_ENEMY < 4) { SPEED_ENEMY += 1; } }
			if (chs == 1) { if (PERS < 250) { PERS += 1; } }
			break;
		case 119:
			if (chs > 0) { chs -= 1; }
			else { chs = 1; }
			break;
		case 115:
			if (chs < 1) { chs += 1; }
			else { chs = 0; }
			break;
		}
		fl.close();
	}
}

void print_choiсe(int place) {
	lock_guard <mutex> lg(mx1);
	vector<string> mn = { "Новая игра", "Настройки", "Авторы", "Рекорд: " };
	int y_menu = 10;
	ClearConsole();
	gxy(55, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	cout << "Лабиринт";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0; i < 4; i++) {
		gxy(55, y_menu);
		if (place == i) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			cout << ">> ";
			cout << mn[i];
			y_menu += 3;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else {
			cout << mn[i];
			if (i == 3) { cout << RECORD_SCORE; }
			y_menu += 3;
		}
	}
}

void Cursor_act() {
	POINT pnt_curs; 
	// закоментированный метод конфликтует с _getch() 

	/*COORD coord;
	DWORD Events;
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD InputRecord;

	DWORD prev_mode;
	GetConsoleMode(hin, &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));*/

	//SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
	while (true) {
		if (!STOP_CURSOR) {
			//ReadConsoleInput(hin, &InputRecord, 1, &Events);
			//coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
			//coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			GetCursorPos(&pnt_curs);
			pnt_curs.x /= 8;
			pnt_curs.y /= 16;
			if (pnt_curs.y == 10 && pnt_curs.x >= 55 && pnt_curs.x <= 65) {
				if (p != 0) { print_choiсe(0); }
				p = 0;
			}
			if (pnt_curs.y == 13 && pnt_curs.x >= 55 && pnt_curs.x <= 65) {
				if (p != 1) { print_choiсe(1); }
				p = 1;
			}
			if (pnt_curs.y == 16 && pnt_curs.x >= 55 && pnt_curs.x <= 65) {
				if (p != 2) { print_choiсe(2); }
				p = 2;
			}
		}
	}
}


bool menu() {
	bool z = true;
	while (z) {
		
		print_choiсe(p);

		char a = _getch();

		switch ((int)a)
		{
		case 13:
			if (p == 0) { 
				STOP_CURSOR = true;
				return 0;
			}
			if (p == 1) {
				STOP_CURSOR = true;
				print_settings();
				STOP_CURSOR = false;
			}
			if (p == 2) {
				STOP_CURSOR = true;
				print_creator();
				STOP_CURSOR = false;
			}
			break;
		case 27:
			STOP_CURSOR = true;
			return 1;
			break;
		case 72:
			if (p > 0) p -= 1;
			else p = 2;
			break;
		case 80:
			if (p < 2) p += 1;
			else p = 0;
			break;
		case 119:
			if (p > 0) p -= 1;
			else p = 2;
			break;
		case 115:
			if (p < 2) p += 1;
			else p = 0;
			break;
		}

		print_choiсe(p);
	}

	STOP_CURSOR = true;

	ClearConsole();
	return 1;
}
