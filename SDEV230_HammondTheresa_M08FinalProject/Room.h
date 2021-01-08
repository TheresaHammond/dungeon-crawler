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
	friend class Item;
private:
	Entity* enemy; // holds enemy (may turn into a list later)
	Chest* chest; // each room can hold 1 chest max
	int x;
	int y;
	std::string map_icon;
	bool is_entrance;
	bool is_exit;
	bool visited;
	int door_count;
	int light;
	int type;
	int iteration; // level of branch pass on map gen (0 for main, ++ for each pass)
	std::string brightness[3] = { "dark", "dim", "well-lit" };
	std::string property[3] = { "mossy", "dry", "damp" };
	std::list<Item*> item_list;
	Door* a_doors[4]; // array of pointers to doors in room (init null)
public:
	Room(void);
	Room(int x, int y, int i); // constructor
	~Room(void); // destructor
	std::list<Item*> get_item_list();
	void set_item_list(std::list<Item*> stuff);
	void add_item(Item* item);
	void describe();
	int get_x();
	int get_y();
	bool get_visited();
	void set_visited();
	Entity*& get_enemy();
	bool is_an_exit(void); // returns whether room is exit or not
};