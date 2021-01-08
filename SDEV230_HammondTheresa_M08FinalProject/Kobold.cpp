#include "Kobold.h"
#include "IronSword.h"
#include "LeatherArmor.h"

using namespace std;

Kobold::Kobold(void) { // constructor
	this->name = "Kobold";
	this->hp = 50;
	this->maxhp = hp;
	this->level = 1;
	this->atk = 3;
	this->def = 3;
	this->weapon = new IronSword;
	this->armor = new LeatherArmor;
}

Kobold::~Kobold(void) { // destructor
	delete weapon; // unless these maybe have a chance to be dropped by enemy?
	delete armor;
}