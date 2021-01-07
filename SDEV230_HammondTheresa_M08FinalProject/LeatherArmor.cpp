#include "LeatherArmor.h"

#include <iostream>

using namespace std;

LeatherArmor::LeatherArmor(void) { // constructor
	this->tier = 1;
	this->name = "Leather Armor";
	this->desc = "Protective gear sewn from toughened animal skin.";
	this->type = "Armor";
	this->effect = 3;
}

