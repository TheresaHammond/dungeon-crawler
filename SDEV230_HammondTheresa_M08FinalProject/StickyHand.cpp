#include "StickyHand.h"

StickyHand::StickyHand(void) { // CONSTRUCTOR
	this->takeable = true;
	this->type = "Weapon";
	this->equippable = true;
	this->name = "Giant Sticky Hand";
	this->desc = "Massive sticky rubber hand. Does 25 damage.";
	this->location = "HERE.";
	this->locations = { "on the floor", "on a shelf", "next to you", "at your feet" }; // list of available interactions
	// randomly generate item location
	list<string>::iterator it = locations.begin();
	for (int i = 0; i < (rand() % (locations.size())); i++) {
		++it;
	}
	this->location = *it;
	this->power = 25;
}
