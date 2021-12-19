#include "Menu.h"
#include "stdlib.h"
#include "windows.h"
#include "stdio.h"
#include "Name.h"
#include "Global.h"
#include "Map_Act.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#define DEF_Key_W 119
#define DEF_Key_A 97
#define DEF_Key_S 115
#define DEF_Key_D 100

using namespace std;

void enemy() {

	int cnt_enemy = 12;

	srand(time(NULL));

	vector<vector<int>> Enemy_pos;
	for (int i = 0; i < cnt_enemy / 4; i++) {
		for (int j = 1; j < 5; j++) {
			while (true) {
				int r1 = 1 + rand() % (MAX_Y - 2);
				int r2 = 1 + rand() % (MAX_X - 2);
				if (Map.Can_Move(r1 - 1, r2, DEF_Key_S, j) && pow((r1 - Y)*(r1 - Y) - (r2 - X)*(r2 - X), 0.5) > 5) {
					Enemy_pos.push_back({ r1, r2, j });
					break;
				}
			}
		}
	}

	for (int i = 0; i < cnt_enemy; i++) {
		if (Enemy_pos[i][2] == ROOM) Map.Draw_pers(Enemy_pos[i][1], Enemy_pos[i][0], ENEMY_PERS, 2);
	}


	while (true) {

		if (CREATE_ENEMY) { // генерируем врагов
			Enemy_pos.empty();
			for (int i = 0; i < cnt_enemy / 4; i++) {
				for (int j = 1; j < 5; j++) {
					while (true) {
						int r1 = 1 + rand() % (MAX_Y - 2);
						int r2 = 1 + rand() % (MAX_X - 2);
						if (Map.Can_Move(r1 - 1, r2, DEF_Key_S, j) && pow((r1 - Y) * (r1 - Y) - (r2 - X) * (r2 - X), 0.5) > 7) {
							Enemy_pos.push_back({ r1, r2, j });
							break;
						}
					}
				}
			}
			CREATE_ENEMY = false;
		}

		if (!STOP_ENEMY) {

			SCORE += 1;
			char enemy_way;
			//clock_t start = clock(); // замеры времени 

			for (int i = 0; i < cnt_enemy; i++) { // алгоритм поиска пути для врагов
				if (Enemy_pos[i][2] != ROOM) { continue; }

				enemy_way = ' ';
				vector<vector<int>> closed(31, vector<int>(121, 0));
				vector<vector<int>> open{ {Y, X} };

				while (enemy_way == ' ') {
					vector<int> dxy{ 0, 0 };

					for (int j = 0; j < open.size(); j++) {

						dxy[0] = open[j][0] - 1;
						dxy[1] = open[j][1];
						if (dxy[0] == Enemy_pos[i][0] && dxy[1] == Enemy_pos[i][1]) {
							enemy_way = 'D';
							break;
						}
						if (0 < dxy[0] && dxy[0] < 30 && 0 < dxy[1] && dxy[1] < 120) {
							if (closed[dxy[0]][dxy[1]] == 0 && Map.Can_Move(open[j][0], open[j][1], DEF_Key_W, ROOM)) {
								closed[dxy[0]][dxy[1]] = 1;
								open.push_back(dxy);
							}
						}
						dxy[0] = open[j][0] + 1;
						dxy[1] = open[j][1];
						if (dxy[0] == Enemy_pos[i][0] && dxy[1] == Enemy_pos[i][1]) {
							enemy_way = 'U';
							break;
						}
						if (0 < dxy[0] && dxy[0] < 30 && 0 < dxy[1] && dxy[1] < 120) {
							if (closed[dxy[0]][dxy[1]] == 0 && Map.Can_Move(open[j][0], open[j][1], DEF_Key_S, ROOM)) {
								closed[dxy[0]][dxy[1]] = 1;
								open.push_back(dxy);
							}
						}
						dxy[0] = open[j][0];
						dxy[1] = open[j][1] - 1;
						if (dxy[0] == Enemy_pos[i][0] && dxy[1] == Enemy_pos[i][1]) {
							enemy_way = 'R';
							break;
						}
						if (0 < dxy[0] && dxy[0] < 30 && 0 < dxy[1] && dxy[1] < 120) {
							if (closed[dxy[0]][dxy[1]] == 0 && Map.Can_Move(open[j][0], open[j][1], DEF_Key_A, ROOM)) {
								closed[dxy[0]][dxy[1]] = 1;
								open.push_back(dxy);
							}
						}
						dxy[0] = open[j][0];
						dxy[1] = open[j][1] + 1;
						if (dxy[0] == Enemy_pos[i][0] && dxy[1] == Enemy_pos[i][1]) {
							enemy_way = 'L';
							break;
						}
						if (0 < dxy[0] && dxy[0] < 30 && 0 < dxy[1] && dxy[1] < 120) {
							if (closed[dxy[0]][dxy[1]] == 0 && Map.Can_Move(open[j][0], open[j][1], DEF_Key_D, ROOM)) {
								closed[dxy[0]][dxy[1]] = 1;
								open.push_back(dxy);
							}
						}
					}
				}

				Map.Delete_pers(Enemy_pos[i][1], Enemy_pos[i][0]);

				if (enemy_way == 'U') { Enemy_pos[i][0] -= 1; }
				if (enemy_way == 'D') { Enemy_pos[i][0] += 1; }
				if (enemy_way == 'L') { Enemy_pos[i][1] -= 1; }
				if (enemy_way == 'R') { Enemy_pos[i][1] += 1; }

				if (Enemy_pos[i][0] == Y && Enemy_pos[i][1] == X) { 
					DEATH = true; 
					STOP_ENEMY = true;
				}

				Map.Draw_pers(Enemy_pos[i][1], Enemy_pos[i][0], ENEMY_PERS, 2);

				//clock_t end = clock(); // замеры времени
				//cout << (double)(end - start) / CLOCKS_PER_SEC;
				//_getch();
			}

			this_thread::sleep_for(chrono::milliseconds(SPEED_ENEMY*100)); // настройка скорости врагов через задержку
		}
	}
}