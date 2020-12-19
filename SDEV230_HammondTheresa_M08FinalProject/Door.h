#pragma once

#include "Openable.h"

#include <iostream>
#include <string>
#include <list>

class Room;

class Door :public Openable {
	friend class Tester;
	friend class Player;
protected:
	Room* a_rooms[2]; // array of pointers to rooms that door connects to (init null)
public:
	Door(void); // default
	Door(Room* current, Room* next); // constructor
	void kick();
	int open_action(Player& player);
};