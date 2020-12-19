#pragma once

#include "Openable.h"
#include "Player.h"

#include <string>
#include <list>

class Chest : public Openable {
	friend class Map; // so map can generate chests and items to put in chests
private:
	bool open;
	bool locked;
	std::list<Item*> items;
	std::list<Item*>::iterator it;
public:
	Chest(void); // constructor
	// void use(Player& player);
	void status();
	bool open_action(Player& player);
};

