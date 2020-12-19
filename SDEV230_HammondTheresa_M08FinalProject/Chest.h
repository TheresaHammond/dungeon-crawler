#pragma once

#include <string>
#include <list>

#include "Player.h"

class Chest : public Item {
	friend class Map; // so map can generate chests and items to put in chests
private:
	bool open;
	bool locked;
	std::list<Item*> items;
	std::list<Item*>::iterator it;
public:
	Chest(void); // constructor
	void use(Player& player);
	void status();
};

