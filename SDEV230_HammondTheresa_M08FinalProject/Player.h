#pragma once
#include "Entity.h"

#include <iostream>
#include <string>
#include <list>

class Room;

class Player :public Entity {
	friend class Map;
	friend class Door;
	friend class Chest;
	friend class Openable;
private:
	std::list<Item*> backpack; // list of pointers to Item class (and subclasses)
	// int carry_limit = 10;
	int move_count; // counts how many times player has changed rooms
	int keyring; // how many keys a player currently has
	bool bigkey; // whether or not player has big key
public:
	Player(void);
	Player(std::string name);
	void addto_backpack(Item* item);
	void open_backpack();
	void examine();
	bool move();
	bool interact(Item* item, int index);
};



