#include "Name.h"
#include "Global.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>

using namespace std;

mutex mx; // защита функций от ошибок из-за многопоточности

MAP::MAP(string way) { // загрузка карты из файла
	ifstream in(way);
	for (int i = 0; i < 120; i++) {
		getline(in, this->Arr[i]);
	}
	in.close();
}

void MAP::Draw_map(int room) { // отрисовка карты
	ClearConsole();
	for (int i = 30 * (room - 1); i < 30 * room; i++) {
		for (int j = 0; j < Arr[i].size(); j++) {
			//cout << Arr[i] << "\n";
			//printf("%s", Arr[i]);
			printf("%c", Arr[i][j]);
		}
		printf("\n");
	}
}

void MAP::Delete_pers(int dx, int dy) { // точечное удаление персонажа
	lock_guard<mutex> lg(mx);
	gxy(dx, dy);
	printf(" ");
}

void MAP::Draw_pers(int dx, int dy, char pers, int clr) { // отрисовка персонажа
	lock_guard<mutex> lg(mx);
	gxy(dx, dy);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
	printf("%c", pers);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

bool MAP::Can_Move(int dy, int dx, int way, int room) { // проверка возможности движение в данную сторону
	lock_guard<mutex> lg(mx);
	switch (way) {
	case 119:
		if (dy + 30 * (room - 1) - 1 < 30 * (room - 1)) { return 0; }
		if (Arr[dy + 30 * (room - 1) - 1].size() <= dx) {
			if (dx < 120) { return 1; }
			else { return 0; }
		}
		if (Arr[dy + 30 * (room - 1) - 1][dx] != 'X') { return 1; };
		return 0;
	case 115:
		if (dy + 30 * (room - 1) + 2 > 30 * room) { return 0; }
		if (Arr[dy + 30 * (room - 1) + 1].size() <= dx) { 
			if (dx < 120) { return 1; }
			else { return 0; }
		}
		if (Arr[dy + 30 * (room - 1) + 1][dx] != 'X') { return 1; }
		return 0;
	case 97:
		if (dx - 1 < 0) { return 0; }
		if (Arr[dy + 30 * (room - 1)].size() <= dx - 1) { 
			if (dx < 120) { return 1; }
			else { return 0; }
		}
		if (Arr[dy + 30 * (room - 1)][dx - 1] != 'X') { return 1; }
		return 0;
	case 100:
		if (dx + 1 > 120) { return 0; }
		if (Arr[dy + 30 * (room - 1)].size() <= dx + 1) { 
			if (dx < 120) { return 1; }
			else { return 0; }
		}
		if (Arr[dy + 30 * (room - 1)][dx + 1] != 'X') { return 1; }
		return 0;
	}
}
