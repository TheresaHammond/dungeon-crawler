#include "Door.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

Door::Door(void) { // def con
}

Door::Door(Room* current, Room* next) { // constructor!
	// cout << "New door constructed!" << endl;
	for (int i = 0; i < 2; i++) {
		a_rooms[i] = 0; // initialize all pointers as null
	}
	this->open = false; // closed and unlocked by default
	this->locked = false;
	this->name = "Door";
	this->desc = "It's a plain wooden door.";
	list<string> locations{ "" }; // leave blank for now
	this->location = "nearby";
	this->takeable = false;
	this->a_rooms[0] = current; // insert connecting rooms to door ref
	this->a_rooms[1] = next;
}

Door::~Door(void) { // destructor
	// cout << "DOOR DELETED." << endl;
}

void Door::status() {
	if (!open && !locked) { // closed and unlocked
		cout << "\n>> The " << name << " is closed." << endl;
	}
	else if (!locked) { // already open
		cout << "\n>> The " << name << " is open." << endl;
	} // is locked (and closed)
	else cout << "\n>>The " << name << " is locked." << endl;
}

void Door::use() {
	if (!open && !locked) { // if closed and unlocked
		cout << "\n>> You open the " << name << "." << endl;
		open = true; // open object
		// prompt for "will you go through?" yes/no
	}
	else if (!locked) { // already open
		cout << "\n>> The " << name << " is already open." << endl;
		// "will you go through? y/n" prompt
	} // else is locked (and closed)
	else cout << "\n>> You try to open the " << name << ", but it's locked." << endl;
}

void Door::kick() {
	cout << ">> The " << name << " rattles." << endl;
}