#include "BigDoor.h"

BigDoor::BigDoor(void) { // def con
	cout << "Default big door constructor!" << endl;
}

BigDoor::BigDoor(Room* current, Room* next) { // constructor!
	cout << "New boss door constructed!" << endl;
	for (int i = 0; i < 2; i++) {
		a_rooms[i] = 0; // initialize all pointers as null
	}
	this->open = false; // boss door always closed & locked by default
	this->locked = true; 
	this->name = "Big Door";
	this->desc = "A massive, gilded door. Requires an equally massive key.";
	list<string> locations{ "" }; // leave blank for now
	this->location = "nearby";
	this->takeable = false;
	this->a_rooms[0] = current; // insert connecting rooms to door ref
	this->a_rooms[1] = next;
}
