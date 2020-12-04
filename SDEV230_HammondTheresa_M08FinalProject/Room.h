#pragma once

#include "Item.h"
#include "Door.h"
#include "Chest.h"

#include <string>
#include <list>

class Room {
	friend class Tester;
	friend class Map; // yay friendship
	friend class Player;
private:
	Chest* chest;
	int x;
	int y;
	std:: string map_icon;
	bool is_entrance;
	bool is_exit;
	bool visited;
	int door_count;
	int light;
	int type;
	int iteration; // level of branch pass on map gen (0 for main, ++ for each pass)
	std::string brightness[3] = { "dark", "dim", "well-lit" };
	std::string property[3] = { "mossy", "dry", "damp" };
	list<Item*> item_list;
	Door* a_doors[4]; // array of pointers to doors in room (init null)
public:
	Room(void);
	Room(int x, int y, int i); // constructor
	~Room(void); // destructor
	list<Item*> get_item_list();
	void set_item_list(list<Item*> stuff);
	void add_item(Item* item);
	void describe();
	int get_x();
	int get_y();
	void set_visited();
};