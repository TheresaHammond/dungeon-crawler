#pragma once

#include "Openable.h"
#include "Player.h"

#include <string>
#include <list>

class Chest : public Openable {
	friend class Map; // so map can generate chests and items to put in chests
private:
	std::list<Item*> items;
	std::list<Item*>::iterator it;
public:
	Chest(void); // constructor
	// void use(Player& player);
	void status();
	int open_action(Player& player);
};

