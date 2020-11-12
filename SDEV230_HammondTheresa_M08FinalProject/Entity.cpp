#include "Entity.h"
#include "Item.h"
#include "Room.h"
#include <iostream>
#include <string>

using namespace std;

Entity::Entity(void) { // CONSTRUCTOR
	this->hp = 100;
	this->str = 3;
	this->def = 3;
	this->intel = 3;
	this->name = "Unknown Entity";
}
void Entity::set_hp(int change) { // hp setter
	this->hp -= change;
}
int Entity::get_hp() { // hp getter
	return this->hp;
}
void Entity::set_str(int change) { // str setter
	this->str = change;
}
int Entity::get_str() { // str getter
	return str;
}
void Entity::set_def(int change) { // def setter
	this->def = change;
}
int Entity::get_def() { // def getter
	return def;
}
void Entity::set_intel(int change) { // intel setter
	this->intel = change;
}
int Entity::get_intel() { // intel getter
	return intel;
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
	cout << "Str: " << str << endl;
	cout << "Def: " << def << endl;
	cout << "Int: " << intel << endl;
	// weapon held and armor worn
}


