#include "IronSword.h"

#include <iostream>

using namespace std;

IronSword::IronSword(void) { // constructor
	this->tier = 1;
	this->name = "Iron Sword";
	this->desc = "A rusted, slightly bent slab of metal.";
	this->type = "Weapon";
	this->effect = 3;
}
