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

	// randomly generate item location (for flavor text)
	this->locations = { " on the floor.", " on a shelf.", " next to you.", " at your feet.", " in a corner." }; // list of available interactions
	list<string>::iterator it = locations.begin();
	for (int i = 0; i < (rand() % (locations.size())); i++) {
		++it;
	}
	this->location = *it;
}

void Item::status() { // shows more information about this thing (using look function) (virtual)
	cout << ">> Nothing else to report about this." << endl;
}

void Item::use(Player& player) { // apply item effect (yay runtime polymorphism!) (virtual)
	cout << "\n>> You use the " << name << "." << endl;
	cout << ">> Nothing happened." << endl;
}

void Item::kick() { // fun stuff (virtual)
	cout << ">> Nothing happened." << endl;
}

void Item::describe() {
	cout << "\n>> [" << name << "]: " << desc << endl;
}

