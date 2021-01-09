#include "Entity.h"
#include "Item.h"
#include "Room.h"

#include <iostream>
#include <string>

using namespace std;

Entity::Entity(void) { // CONSTRUCTOR
	this->gems = 0;
	this->hp = 1;
	this->level = 0;
	this->xp = 0;
	this->maxxp = 0;
	this->maxhp = hp;
	this->atk = 0;
	this->def = 0;
	this->name = "Unknown Entity";
	this->weapon = nullptr;
	this->armor = nullptr;
}

void Entity::attack(Entity& target) { // physical attack
	int pwr;
	int dmg;

	// check whether target is player or not (for flavor text)
	if (target.type == "Player") 
		cout << "\n>> The enemy " << name << " attacks you!" << endl; // target is player
	else 
		cout << "\n>> You attack the enemy " << target.name << "!" << endl; // target is enemy

	// calculate attacker's attack power
	if (weapon) pwr = weapon->effect + atk; // if attacker has weapon, add its effect to damage power
	else pwr = atk;

	// calculate damage
	dmg = pwr - target.def; // subtract target's defense from attacker's attack power
	if (dmg < 0) dmg = 0; // limit negative values to 0

	// apply damage to target
	target.hp = (target.hp - dmg);
	if (target.hp < 0) target.hp = 0; // limit negative values to 0

	// flavor text
	if (target.type == "Player")
		cout << ">> You take " << dmg << " damage!" << endl; // target is player
	else 
		cout << ">> The enemy " << target.name << " takes " << dmg << " damage!" << endl; // target is enemy
}

void Entity::set_xp(int value) { // xp setter
	this->xp = value;
}

int Entity::get_xp() { // xp getter
	return xp;
}

void Entity::set_hp(int value) { // hp setter
	this->hp = value;
}

int Entity::get_hp() { // hp getter
	return hp;
}

void Entity::set_maxhp(int value) {
	this->maxhp = value;
}

int Entity::get_maxhp() {
	return maxhp;
}

void Entity::set_atk(int value) { // str setter
	this->atk = value;
}

int Entity::get_atk() { // str getter
	return atk;
}

void Entity::set_def(int value) { // def setter
	this->def = value;
}

int Entity::get_def() { // def getter
	return def;
}

void Entity::set_room(Room* room) { // room setter
	this->room = room;
}
Room*& Entity::get_room() { // room getter
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


