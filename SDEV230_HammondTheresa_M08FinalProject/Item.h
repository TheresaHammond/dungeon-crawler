#pragma once

#include <string>
#include <list>

using namespace std;

class Item { // base item class (should this be an abstract class...?)
	friend class Player;
protected:
	bool multiuse; // flag for whether item can be used more than once
	string name;
	string desc;
	string location;
	list<string> locations; // list of available interactions
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