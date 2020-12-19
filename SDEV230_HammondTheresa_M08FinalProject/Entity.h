#pragma once

#include "Item.h"

#include <iostream>
#include <string>

class Room;

class Entity {
protected:
	int hp; // health
	std::string name;
	Room* room; // pointer to current location
	int str; // strength
	int def; // defense
	int intel; // intelligence
public:
	Entity(void);
	void set_hp(int change);
	int get_hp();
	void set_intel(int change);
	int get_intel();
	void set_str(int change);
	int get_str();
	void set_def(int change);
	int get_def();
	void set_room(Room* room);
	Room* get_room();
	void set_name(std::string name);
	std::string get_name();
	void get_stats();
};