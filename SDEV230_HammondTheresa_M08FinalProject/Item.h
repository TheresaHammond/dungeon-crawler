#pragma once

#include <string>
#include <list>

using namespace std;

class Item { // base item class (should this be an abstract class...?)
protected:
	string name;
	string desc;
	string location;
	list<string> locations; // list of available interactions
public:
	bool takeable;
	Item(void);
	string get_name();
	string get_location();
	string get_desc();
	virtual void status();
	virtual void use();
	virtual void kick();
};