#include "Chest.h"

#include <iostream>
#include <list>

using namespace std;

Chest::Chest(void) { // constructor
	this->open = false; // closed and unlocked by default
	this->locked = false;
	// this->location = "nearby";
	// this->takeable = false;
	list<Item*>::iterator it = items.begin();
	this->name = "Chest";
	this->desc = "It's an ordinary wooden chest.";
}

void Chest::use(Player& player) { // interaction between player and chest
	if (locked) {
		cout << "\n>> The " << name << " is locked.";
		// if player has a key in their inventory, prompt them to use a key to open the chest
	}
	if (!open) {
		cout << "\n>> You open the " << name << "." << endl;
		this->open = true;
	}
	if (open) {
		if (items.empty()) cout << "\n>> The " << name << " is empty." << endl;
		else { // access items inside
			int choice = (items.size() + 1); // cancel by default
			cout << "\n What will you take?" << endl;
			for (it = items.begin(); it != items.end(); ++it) { // list items
				cout << ((distance(items.begin(), it)) + 1) << " . . . " << (*it)->get_name() << endl;
			}
			cout << items.size() << " . . . Take All" << endl;
			cout << (items.size() + 1) << " . . . Cancel" << endl;
			cout << "Enter choice: ";
			cin >> choice;

			// Take All
			if (choice == items.size()) { // add all items in chest to player backpack
				for (it = items.begin(); it != items.end(); ++it) {
					player.addto_backpack(*it); // add pointer to player backpack
					items.erase(it); // delete pointer from list
				}
			}
			// Cancel
			else if (choice >= (items.size() + 1)) { // don't take anything and exit menu
				cout << "\n>> You decide not to take anything." << endl;
			}
			// Item chosen
			else { // select that item and add it to player backpack
				it = items.begin();
				while ((distance(items.begin(), it) + 1) != choice) {
					++it; // iterate until it matches choice (chosen item located)
				}
				player.addto_backpack(*it); // add pointer to player backpack
				items.erase(it); // delete pointer from list
			}
		}
	}
}

void Chest::status() {
	if (locked) cout << "\n>> The " << name << " is locked." << endl;
	else if (!open) cout << "\n>> The " << name << " is closed." << endl;
	else cout << "\n>> The " << name << " is open." << endl;
}