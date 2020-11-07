#pragma once
#include "Item.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Door :public Item {
protected:
	bool open;
	bool locked;
public:
	Door(void);
	void use();
	void kick();
	void status();
};