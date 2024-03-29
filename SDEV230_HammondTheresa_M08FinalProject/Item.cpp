#include "Item.h"

#include <string>
#include <iostream>
#include <list>

using namespace std;

Item::Item(void) { // CONSTRUCTOR
	this->multiuse = true; // whether item can be used multiple times (or just once)
	this->takeable = true;
	this->equippable = false;
	this->name = "Default Item";
	this->desc = "This item does nothing.";
	this->type = "Generic Item Type";
	this->tier = 0; // (0 for base/structural items)
	this->effect = 0;
	this->dir = ""; // only for doors (filled in later)

	// randomly generate item location (for flavor text)
	this->locations = { " on the floor.", " on a shelf.", " next to you.", " at your feet.", " in a corner." }; // list of available interactions
	list<string>::iterator it = locations.begin();
	for (int i = 0; i < (rand() % (locations.size())); i++) {
		++it;
	}
	this->location = *it;
}

void Item::status() { // shows more information about this thing (using look function) (virtual)
	// cout << ">> Nothing else to report about this." << endl;
}

int Item::use(Player& player) { // apply item effect (yay runtime polymorphism!) (virtual)
	cout << "\n>> You use the " << name << "." << endl;
	cout << ">> Nothing happens." << endl;
	return 0; // loop through INTERACT again
}

void Item::kick() { // fun stuff (virtual)
	cout << ">> Nothing happens." << endl;
}

void Item::describe() {
	// provide item info
	cout << "\n>> [" << name << "]: (" << type << ")" << endl;
	cout << ">> " << desc;

	// show modifiers based on item type
	if (effect > 0) {
		if (type == "Weapon")
			cout << " Deals " << effect << " base damage." << endl;
		if (type == "Consumable")
			cout << " Heals " << effect << " HP." << endl;
		if (type == "Armor")
			cout << " Provides " << effect << " base defense." << endl;
	}
}

