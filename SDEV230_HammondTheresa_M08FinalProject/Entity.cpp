#include "Entity.h"
#include "Item.h"
#include "Room.h"
#include <iostream>
#include <string>

using namespace std;

Entity::Entity(void) { // CONSTRUCTOR
	this->hp = 1;
	this->name = "Unknown Entity";
}
void Entity::set_hp(int change) { // hp setter
	this->hp += change;
}
int Entity::get_hp() { // hp getter
	return this->hp;
}
void Entity::set_room(Room& room) { // room setter
	this->room = room;
}
Room& Entity::get_room() { // room getter
	return this->room;
}
void Entity::set_name(string name) { // name setter
	this->name = name;
}
string Entity::get_name() { // name getter
	return name;
}
void Entity::get_stats() { // draws current entity stats
	cout << "\nName: " << name << endl;
	cout << "HP: " << hp << endl;
}


