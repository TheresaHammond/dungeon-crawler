#include "HealthPotion.h"

HealthPotion::HealthPotion(void) { // CONSTRUCTOR
	this->multiuse = false;
	this->name = "Health Potion";
	this->desc = "Refills player's HP by 20.";
	this->effect = 20;
}

