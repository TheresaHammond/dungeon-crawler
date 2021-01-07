#include "Entity.h"
#include "Item.h"
#include "Room.h"
#include <iostream>
#include <string>

using namespace std;

Entity::Entity(void) { // CONSTRUCTOR
	this->hp = 10;
	this->level = 0;
	this->xp = 0;
	this->maxxp = 0;
	this->maxhp = hp;
	this->atk = 3;
	this->def = 3;
	this->intel = 3;
	this->name = "Unknown Entity";
	this->weapon = nullptr;
	this->armor = nullptr;
}
void Entity::set_hp(int change) { // hp setter
	this->hp = change;
}
int Entity::get_hp() { // hp getter
	return this->hp;
}
void Entity::set_str(int change) { // str setter
	this->atk = change;
}
int Entity::get_str() { // str getter
	return atk;
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
void Entity::set_room(Room* room) { // room setter
	this->room = room;
}
Room* Entity::get_room() { // room getter
	return this->room;
}
void Entity::set_name(string name) { // name setter
	this->name = name;
}
string Entity::get_name() { // name getter
	return name;
}
void Entity::get_stats() { // draws current entity stats
	// vitals
	cout << "\nNAME: " << name << endl;

	cout << "LEVEL: " << level << endl;
	cout << "NEXT: " << (maxxp - xp) << " XP" << endl;

	cout << "HP: " << hp << "/" << maxhp << endl;

	cout << "ATK: " << atk; // display any cumulative modifiers (weapon, spell, etc)
	if (weapon) cout << " (+" << weapon->effect << ")";
	cout << endl;

	cout << "DEF: " << def; // display any cumulative modifiers (weapon, spell, etc)
	if (armor) cout << " (+" << armor->effect << ")";
	cout << endl;
	// cout << "Int: " << intel << endl;

	// weapon held
	cout << "WEAPON: ";
	if (weapon) cout << weapon->name << " (+" << weapon->effect << " ATK)" << endl;
	else cout << "None" << endl;
	 
	// armor worn
	cout << "ARMOR: ";
	if (armor) cout << armor->name << " (+" << armor->effect << " DEF)" << endl;
	else cout << "None" << endl;

	// status? (you are fine, you are injured, you are poisoned, etc) (can be multiple, in a list)
	cout << "STATUS: ";
	// health status
	if (status_list.empty() && (hp > (maxhp / 2))) cout << "Fine";
	else if (hp <= (maxhp / 4)) cout << "Critically injured";
	else if (hp <= (maxhp / 2)) cout << "Injured";
	// status effects
	// (these will come from list, separate with comma)
	cout << endl;
}


