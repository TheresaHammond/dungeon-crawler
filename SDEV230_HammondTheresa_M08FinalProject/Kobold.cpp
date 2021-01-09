#include "Kobold.h"
#include "IronSword.h"
#include "LeatherArmor.h"

using namespace std;

Kobold::Kobold(void) { // constructor
	this->name = "Kobold";
	this->type = "Enemy";
	this->background = "Fighter";
	this->xp = 20; // xp value given when defeated
	this->hp = 10;
	this->maxhp = hp;
	this->level = 1;
	this->atk = 3;
	this->def = 3;
	this->weapon = new IronSword;
	this->armor = new LeatherArmor;
	this->gems = (rand() % 10 + 1) + level; // between 1 and 10 gems plus level modifier
}

Kobold::~Kobold(void) { // destructor
	delete weapon; // unless these maybe have a chance to be dropped by enemy?
	delete armor;
}