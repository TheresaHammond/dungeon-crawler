#pragma once

#include "Item.h"
#include "Room.h"
#include <iostream>
#include <string>

using namespace std;

class Entity {
protected:
	int hp;
	string name;
	Room room;
public:
	Entity(void);
	void set_hp(int change);
	int get_hp();
	void set_room(Room& room);
	Room& get_room();
	void set_name(string name);
	string get_name();
	void get_stats();
};