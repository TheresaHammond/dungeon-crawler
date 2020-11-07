#include "Door.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

Door::Door(void) { // CONSTRUCTOR
	this->open = false; // closed and unlocked by default
	this->locked = false;
	this->name = "Door";
	this->desc = "It's a plain wooden door.";
	list<string> locations{ "" }; // leave blank for now
	this->location = "nearby";
	this->takeable = false;
}

void Door::status() {
	if (!open && !locked) { // closed and unlocked
		cout << ">> The " << this->get_name() << " is closed." << endl;
	}
	else if (!locked) { // already open
		cout << ">> The " << this->get_name() << " is open." << endl;
	} // is locked (and closed)
	else cout << ">>The " << this->get_name() << " is locked." << endl;
}

void Door::use() {
	if (!open && !locked) { // if closed and unlocked
		cout << "\n>> You open the " << this->get_name() << "." << endl;
		open = true; // open object
		// prompt for "will you go through?" yes/no
	}
	else if (!locked) { // already open
		cout << "\n>> The " << this->get_name() << " is already open." << endl;
	} // is locked (and closed)
	else cout << "\n>> You try to open the " << this->get_name() << ", but it's locked." << endl;
}

void Door::kick() {
	cout << ">> The " << this->get_name() << " rattles." << endl;
}