#pragma once

#include "Item.h"

#include <iostream>
#include <string>

class Room;

class Entity {
protected:
	int gems; // currency
	int hp; // current health value
	int maxhp; // max health value
	int level; // current level
	int xp; // experience
	int maxxp; // max exp to next level
	std::string name;
	std::string type; // identifier (player, enemy, NPC, etc)
	Room* room; // pointer to current location
	int atk; // attack power
	int def; // defense
	Item* weapon;
	Item* armor;
	std::list<std::string> status_list; // list of statuses inflicted on the player
public:
	Entity(void);
	void attack(Entity& target); // attack action of entity (damage calc)
	void set_xp(int value);
	int get_xp();
	void set_hp(int value);
	int get_hp();
	void set_maxhp(int value);
	int get_maxhp();
	void set_atk(int value);
	int get_atk();
	void set_def(int value);
	int get_def();
	void set_room(Room* room);
	Room*& get_room();
	void set_name(std::string name);
	std::string get_name();
	void get_stats();
};