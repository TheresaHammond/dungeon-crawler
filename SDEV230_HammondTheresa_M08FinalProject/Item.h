#pragma once

#include <string>
#include <list>

class Player;

class Item { // base item class (should this be an abstract class...?)
	friend class Player;
	friend class Chest;
	friend class Room;
protected:
	bool multiuse; // flag for whether item can be used more than once
	std::string name;
	std::string desc;
	std::string location;
	std::list<std::string> locations; // list of available interactions
public:
	bool takeable;
	bool equippable;
	Item(void);
	virtual void status();
	virtual int use(Player& player);
	virtual void kick();
	void describe();
};