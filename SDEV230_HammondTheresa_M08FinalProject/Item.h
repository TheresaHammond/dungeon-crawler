#pragma once

#include <string>
#include <list>

using namespace std;

class Item { // base item class (should this be an abstract class...?)
protected:
	string name;
	string type;
	string desc;
	string location;
	list<string> locations; // random in-room location for flavor text
	int power;
public:
	bool takeable;
	bool equippable;
	Item(void);
	string get_name();
	string get_location();
	string get_desc();
	virtual void status();
	virtual void use();
	virtual void kick();
};