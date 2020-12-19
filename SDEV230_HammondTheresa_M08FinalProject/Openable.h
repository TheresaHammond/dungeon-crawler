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
	void use(Player& player);
	void status();
	virtual bool open_action(Player& player);
};

