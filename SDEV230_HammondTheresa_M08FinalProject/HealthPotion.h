#pragma once

#include "Item.h"

class HealthPotion :public Item {
public:
	HealthPotion(void);
	int use(Player& player);
};



