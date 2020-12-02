#include "Room.h"
#include "Door.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

Room::Room(void) { // CONSTRUCTOR
	cout << "Wrong room constructor!" << endl;
}
Room::Room(int i, int j) { // CONSTRUCTOR
	cout << "Room created" << "(" << i << ", " << j << ")" << endl;
	this->x = i;
	this->y = j;
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
	for (int i = 0; i < 4; i++) {
		a_doors[i] = 0; // initialize all pointers as null
	}
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
		if (door_count > 1) { // singular/plural
			cout << "\n>> There are " << door_count << " doors.";
		}
		else cout << "\n>> There is " << door_count << " door. ";
		// if there are any items in the room, show the items! (if light level)
		if (!item_list.empty()) { 
			for (list<Item*>::iterator it = item_list.begin(); it != item_list.end(); ++it) {
				cout << "\n>> You see a " << (*it)->get_name() << " " << (*it)->get_location() << ".";
			}
		}
	//}
	cout << endl;
}
