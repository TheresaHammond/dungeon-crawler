#pragma once

class Map { // the dungeon map
private:
	int size = 3;
	int entrance_x = 0;
	int entrance_y = 0;
	int exit_x = size;
	int exit_y = size;
public:
	Map(void);
	void map_generate();
};
