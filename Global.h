#include "Map_Act.h"

extern const int MAX_X;
extern const int MAX_Y;
extern const char ENEMY_PERS;
extern char PERS;
extern int X;
extern int Y;
extern int ROOM;
extern MAP Map;
extern bool STOP;
extern bool STOP_ENEMY;
extern bool STOP_CURSOR;
extern int SCORE;
extern int SPEED_ENEMY;
extern bool DEATH;
extern bool CREATE_ENEMY;
extern int RECORD_SCORE;
void get_settings_from_file();
void totalClearScreen();
void ClearConsole();