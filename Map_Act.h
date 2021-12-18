#pragma once
#include <vector>
#include <string>

class MAP {
private:
	std::vector<std::string> Arr{ 120, "" };
public:
	MAP(std::string way);
	void Draw_map(int room);
	void Delete_pers(int dx, int dy);
	void Draw_pers(int dx, int dy, char pers, int clr);
	bool Can_Move(int dx, int dy, int way, int room);
};
