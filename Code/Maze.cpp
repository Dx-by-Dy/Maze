#include "Name.h"
#include "Menu.h"
#include "Enemy.h"
#include "Map_Act.h"
#include "Global.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

void restart(){ // обновляем глобальные переменные
	X = 59;
	Y = 16;
	ROOM = 1;
	SCORE = 0;
	DEATH = false;
	CREATE_ENEMY = true;
	totalClearScreen();
	ClearConsole();

	Map.Draw_map(ROOM);
	Map.Draw_pers(X, Y, PERS, 7);
	get_settings_from_file();
}


void death(){
	ClearConsole();
	gxy(55, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("ВЫ ПОГИБЛИ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gxy(54, 15);
	printf("ВАШ СЧЁТ: %d", SCORE);
	gxy(45, 20);
	printf("Нажмите любую кнопку для продолжения");
	if (RECORD_SCORE < SCORE) { // обновляем рекорд
		ofstream fl("settings.txt");
		fl << SPEED_ENEMY << "\n" << (int)PERS << "\n" << SCORE;
		RECORD_SCORE = SCORE;
		fl.close();
	}
	_getch();
	STOP_CURSOR = false;
	STOP = menu();
	STOP_CURSOR = true;
	if (!STOP) { restart(); }
	STOP_ENEMY = STOP;
}


int main()
{
	setlocale(LC_ALL, "rus");
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
	ShowConsoleCursor(false); //делаем каретку невидимой

	get_settings_from_file(); // получаем данные с файла

	start();
	thread Cursor(Cursor_act); // поток мыши в меню
	STOP = menu();
	
	if (!STOP) {
		Map.Draw_map(ROOM);
		Map.Draw_pers(X, Y, PERS, 7);
	}

	thread Enemy_move(enemy); // поток врагов

	while (true) { // основной поток
		if (DEATH) { death(); }
		if (STOP) { break; }

		char a = _getch(); // фиксируем нажатия

		Map.Delete_pers(X, Y);

		switch ((int)a){ // обрабатываем нажатия
		case 27:
			if (!STOP) {
				STOP_ENEMY = true;
				STOP_CURSOR = false;
				STOP = menu();
				if (!STOP) { Map.Draw_map(ROOM); }
				STOP_CURSOR = !STOP;
				STOP_ENEMY = STOP;
			}
		case 119:
			if (Y != 0) {
				if (Map.Can_Move(Y, X, (int)a, ROOM)) {
					Y -= 1;
					break;
				}
			}
			else {
				if (ROOM == 2) { ROOM = 1; }
				if (ROOM == 4) { ROOM = 3; }
				STOP_ENEMY = true;
				this_thread::sleep_for(chrono::milliseconds(40)); // задержка для перехода в другую комнату 
				Map.Draw_map(ROOM);
				STOP_ENEMY = false;
				Y = 29;
			}
			break;
		case 115:
			if (Y != 29) {
				if (Map.Can_Move(Y, X, (int)a, ROOM)) {
					Y += 1;
					break;
				}
			}
			else {
				if (ROOM == 1) { ROOM = 2; }
				if (ROOM == 3) { ROOM = 4; }
				STOP_ENEMY = true;
				this_thread::sleep_for(chrono::milliseconds(40));
				Map.Draw_map(ROOM);
				STOP_ENEMY = false;
				Y = 0;
			}
			break;
		case 97:
			if (X != 0) { 
				if (Map.Can_Move(Y, X, (int)a, ROOM)) {
					X -= 1;
					break;
				}
			}
			else {
				if (ROOM == 3) { ROOM = 1; }
				if (ROOM == 4) { ROOM = 2; }
				STOP_ENEMY = true;
				this_thread::sleep_for(chrono::milliseconds(40));
				Map.Draw_map(ROOM);
				STOP_ENEMY = false;
				X = 119;
			}
			break;
		case 100:
			if (X != 119) {
				if (Map.Can_Move(Y, X, (int)a, ROOM)) {
					X += 1;
					break;
				}
			}
			else {
				if (ROOM == 1) { ROOM = 3; }
				if (ROOM == 2) { ROOM = 4; }
				STOP_ENEMY = true;
				this_thread::sleep_for(chrono::milliseconds(40)); 
				Map.Draw_map(ROOM);
				STOP_ENEMY = false;
				X = 0;
			}
			break;
		}

		Map.Draw_pers(X, Y, PERS, 7);

		//this_thread::sleep_for(chrono::milliseconds(300));
	}

	Enemy_move.detach();
	Cursor.detach();

	return 0;
}