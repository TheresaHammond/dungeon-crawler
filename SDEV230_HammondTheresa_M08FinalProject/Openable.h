// This is an Interface class for code that Doors, Chests, etc share

#pragma once

#include "Item.h"

class Player;

class Openable : public Item {
protected:
	bool open;
	bool locked;
public:
	Openable(void);
	virtual int use(Player& player);
	void status();
	virtual int open_action(Player& player);
};

