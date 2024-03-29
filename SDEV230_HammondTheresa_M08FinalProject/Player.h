#pragma once
#include "Entity.h"

#include <iostream>
#include <string>
#include <list>

class Room;
class Door;

class Player :public Entity {
	friend class Map;
	friend class Door;
	friend class Chest;
	friend class Openable;
	friend class BigDoor;
private:
	std::list<Item*> backpack; // list of pointers to Item class (and subclasses)
	// int carry_limit = 10;
	int move_count; // counts how many times player has changed rooms
	int keyring; // how many keys a player currently has
	bool bigkey; // whether or not player has big key
public:
	Player(void);
	Player(std::string name, std::string background);
	void addto_backpack(Item* item);
	void open_backpack();
	void examine();
	bool move_menu();
	bool move(Door& door);
	bool interact(Item* item, int index);
	void status_menu();
	void level_up();
};



