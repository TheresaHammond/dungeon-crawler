#pragma once
#include "Door.h"

// BOSS DOOR
class BigDoor :public Door {
public:
	BigDoor(void);
	BigDoor(Room* current, Room* next);
};

