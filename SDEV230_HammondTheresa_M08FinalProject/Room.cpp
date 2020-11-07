#include "Room.h"
#include "Door.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

Room::Room(void) { // CONSTRUCTOR
	this->x = 0;
	this->y = 0;
	this->exists = true;
	this->is_entrance = false;
	this->is_exit = false;
	this->visited = false;
	this->map_icon = "[ ]";
	this->doors = 2;
	this->light = rand() % 2; // generate random light level
	this->type = rand() % 2; // generate room property
	for (int i = 0; i < doors; i++) { // add door items to list of room items
		item_list.push_front(new Door); // always in front
	}
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
	cout << "\n>> You find yourself in a " << brightness[light] << ", " << property[type] << " room.";
	if (light == 0) { // light level too low
		cout << "\n>> It is too dark to see anything.";
	}
	else {
		if (doors > 1) { // show doors
			cout << "\n>> There are " << doors << " doors.";
		}
		else cout << "\n>> There is " << doors << " door. ";
		if (!item_list.empty()) { // if there are any items in the room, show the items! (if light level)
			for (list<Item*>::iterator it = item_list.begin(); it != item_list.end(); ++it) {
				cout << "\n>> You see a " << (*it)->get_name() << " " << (*it)->get_location() << ".";
			}
		}
	}
	cout << endl;
}
