#pragma once

#include "Item.h"

#include <iostream>
#include <string>
#include <list>

class Room;

class Door :public Item {
	friend class Tester;
	friend class Player;
protected:
	bool open;
	bool locked;
	Room* a_rooms[2]; // array of pointers to rooms that door connects to (init null)
public:
	Door(void); // default
	Door(Room* current, Room* next); // constructor
	~Door(void); // destructor
	void use();
	void kick();
	void status();
};