#pragma once
#include "Door.h"

// BOSS DOOR
class BigDoor :public Door {
public:
	BigDoor(void);
	BigDoor(Room* current, Room* next);
	void kick();
	int use(Player& player);
};

