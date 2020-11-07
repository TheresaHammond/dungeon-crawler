#pragma once

#include "Item.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Room {
private:
	int y;
	int x;
	string map_icon;
	bool exists;
	bool is_entrance;
	bool is_exit;
	bool visited;
	int doors;
	int light;
	int type;
	string brightness[3] = { "dark", "dim", "well-lit" };
	string property[3] = { "mossy", "dry", "damp" };
	list<Item*> item_list;
public:
	Room(void); // constructor
	list<Item*> get_item_list();
	void set_item_list(list<Item*> stuff);
	void add_item(Item* item);
	void describe();
	void look();
};