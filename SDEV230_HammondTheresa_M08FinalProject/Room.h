#pragma once

#include "Item.h"
#include "Door.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Room {
	friend class Tester;
	friend class Map; // yay friendship
	friend class Player;
private:
	int x;
	int y;
	string map_icon;
	// bool exists;
	bool is_entrance;
	bool is_exit;
	bool visited;
	int door_count;
	int light;
	int type;
	string brightness[3] = { "dark", "dim", "well-lit" };
	string property[3] = { "mossy", "dry", "damp" };
	list<Item*> item_list;
	Door* a_doors[4]; // array of pointers to doors in room (init null)
public:
	Room(void);
	Room(int i, int j); // constructor
	list<Item*> get_item_list();
	void set_item_list(list<Item*> stuff);
	void add_item(Item* item);
	void describe();
	int get_x();
	int get_y();
	void set_visited();
	// void look();
};