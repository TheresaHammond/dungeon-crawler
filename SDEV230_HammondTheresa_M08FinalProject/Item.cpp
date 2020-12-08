#include "Item.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

Item::Item(void) { // CONSTRUCTOR
	this->multiuse = false;
	this->takeable = true;
	this->equippable = false;
	this->name = "Default Item";
	this->desc = "This item does nothing.";
	this->location = "HERE.";
	this->locations = { "on the floor", "on a shelf", "next to you", "at your feet" }; // list of available interactions
	// randomly generate item location
	list<string>::iterator it = locations.begin();
	for (int i = 0; i < (rand() % (locations.size())); i++) {
		++it;
	}
	this->location = *it;
}
string Item::get_name() { // name getter
	return name;
}
string Item::get_location() { // location getter
	return location;
}
string Item::get_desc() { // description getter
	return desc;
}
void Item::status() { // shows more information about this thing (using look function) (virtual)
	cout << ">> Nothing else to report about this." << endl;
}
void Item::use() { // apply item effect (yay runtime polymorphism!) (virtual)
	cout << "\n>> You use the " << name << "." << endl;
	cout << ">> Nothing happened." << endl;
}
void Item::kick() { // fun stuff (virtual)
	cout << ">> Nothing happened." << endl;
}

void Item::describe() {
	cout << "\n>> [" << name << "]: " << desc << endl;
}

