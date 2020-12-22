#include "HealthPotion.h"

#include <iostream>

using namespace std;

HealthPotion::HealthPotion(void) { // CONSTRUCTOR
	this->multiuse = false;
	this->name = "Health Potion";
	this->desc = "Refills player's HP by 20.";
	this->effect = 20;
}

int HealthPotion::use(Player& player) {
	// return TRUE goes back to MAIN
	// return FALSE loops again through INTERACT
	cout << "\n>> You use the " << name << "." << endl;
	cout << ">> This doesn't do anything yet!" << endl;
	return 0; // go back to INTERACT
}

