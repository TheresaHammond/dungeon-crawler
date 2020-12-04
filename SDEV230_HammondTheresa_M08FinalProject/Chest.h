#pragma once

#include <string>
#include <list>

#include "Player.h"

class Chest {
	friend class Map; // so map can generate chests and items to put in chests
private:
	bool open;
	bool locked;
	std::string name;
	std::string desc;
	list<Item*> items;
	list<Item*>::iterator it;
public:
	Chest(void); // constructor
	void use(Player& player);
	void status();
};

