#include "HealthPotion.h"

#include <iostream>

using namespace std;

HealthPotion::HealthPotion(void) { // CONSTRUCTOR
	this->multiuse = false;
	this->name = "Health Potion";
	this->desc = "Refills player's HP by 20.";
	this->effect = 20;
}

void HealthPotion::use() {
	cout << "\n>> You use the " << name << "." << endl;
	cout << ">> This doesn't do anything yet!" << endl;
}

