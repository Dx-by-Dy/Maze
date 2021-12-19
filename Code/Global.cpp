#include "Map_Act.h"
#include <fstream>
#include <iostream>
#include <Windows.h>

// глобальные переменные и функции

extern const int MAX_X = 120;
extern const int MAX_Y = 30;
extern const char ENEMY_PERS = 42;
extern int X = 59;
extern int Y = 16;
extern int ROOM = 1;
extern MAP Map("Map.txt");
extern bool STOP = false;
extern bool STOP_ENEMY = false;
extern bool STOP_CURSOR = false;
extern int SCORE = 0;
extern int SPEED_ENEMY = 2;
extern char PERS = 64;
extern bool DEATH = false;
extern bool CREATE_ENEMY = false;
extern int RECORD_SCORE = 0;

void get_settings_from_file() {
	std::ifstream fl("Settings.txt");
	int s;
	fl >> SPEED_ENEMY >> s >> RECORD_SCORE;
	PERS = (char)s;
	fl.close();
}

void totalClearScreen() {
	COORD c = { 0, 0 };
	DWORD nKol = 0;
	size_t xy = 30 * 120;
	FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0, xy, c, &nKol);
}

void ClearConsole() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}