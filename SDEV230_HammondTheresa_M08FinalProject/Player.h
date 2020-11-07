#pragma once
#include "Entity.h"
#include "Item.h"
#include "Room.h"
#include <iostream>
#include <string>

class Player :public Entity {
private:
	list<Item*> backpack; // list of pointers to Item class (and subclasses)
	int carry_limit = 10;
public:
	Player(void);
	void addto_backpack(Item* item);
	void open_backpack();
	void look();
};



