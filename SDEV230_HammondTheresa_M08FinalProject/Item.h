#pragma once

#include <string>
#include <list>

class Player;

class Item { // base item class (should this be an abstract class...?)
	friend class Entity;
	friend class Player;
	friend class Chest;
	friend class Room;
protected:
	int tier; // rarity/level of item (0 to ?) (used for dungeon generation)
	int effect; // damage/health/defense value
	bool multiuse; // flag for whether item can be used more than once
	std::string name;
	std::string desc;
	std::string type; // weapon, armor, etc
	std::string location;
	std::list<std::string> locations; // list of available interactions
	std::string dir; // only for doors
public:
	bool takeable; // for things that can be put in backpack
	bool equippable; // for weapons and armor/accessories
	Item(void);
	virtual void status();
	virtual int use(Player& player);
	virtual void kick();
	virtual void describe();
};