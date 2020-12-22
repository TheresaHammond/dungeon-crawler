#include "Room.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;

Room::Room(void) { // CONSTRUCTOR
	// cout << "Wrong room constructor!" << endl;
}
Room::Room(int x, int y, int i) { // CONSTRUCTOR
	// cout << "Room created" << "(" << x << ", " << y << ")" << endl;
	this->chest = nullptr;
	this->x = x;
	this->y = y;
	this->iteration = i;
	this->is_entrance = false;
	this->is_exit = false;
	this->visited = false;
	this->map_icon = "[ ]";
	this->door_count = 0;
	this->light = rand() % 2; // generate random light level
	this->type = rand() % 2; // generate room property
	/* for (int i = 0; i < doors; i++) { // add door items to list of room items
		item_list.push_front(new Door); // always in front
	} */
	for (int k = 0; k < 4; k++) {
		a_doors[k] = 0; // initialize all pointers as null
	}
}

Room::~Room(void) { // destructor
	// cout << "ROOM DELETED." << endl;
}

bool Room::is_an_exit(void) {
	return is_exit;
}

int Room::get_x() {
	return x;
}
int Room::get_y() {
	return y;
}
void Room::set_visited() {
	this->visited = true;
}
// ADD ITEMS TO ROOM INVENTORY
void Room::add_item(Item* item) { 
	item_list.push_back(item);
}
list<Item*> Room::get_item_list() { // get list of items in room
	return item_list;
}
void Room::set_item_list(list<Item*> stuff) { // update list of items in room
	this->item_list = stuff;
}
// DESCRIBE CURRENT ROOM
void Room::describe() {
	if (!visited) cout << "\n>> You find yourself in a " << brightness[light] << ", " << property[type] << " room.";
	else cout << "\n>> This room is " << brightness[light] << " and " << property[type] << ".";

	/* if (light == 0) { // light level too low
		cout << "\n>> It is too dark to see anything.";
	} */
	//else {
		// show how many doors are in room
	cout << "\n>> The room has " << door_count;
	if (door_count == 1) cout << " door. ";
	else cout << " doors."; 

	// if chest in room, show it in description
	if (chest) cout << "\n>> There is a " << chest->name << chest->location;

	// if there are any items in the room, show the items (if light level)
	if (!item_list.empty()) { 
		for (list<Item*>::iterator it = item_list.begin(); it != item_list.end(); ++it) {
			cout << "\n>> You see a " << (*it)->name << (*it)->location;
		}
	}
	//}
	cout << endl;
}
