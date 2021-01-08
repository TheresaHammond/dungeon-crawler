#include "Chest.h"

#include <iostream>
#include <list>

using namespace std;

Chest::Chest(void) { // constructor
	this->locked = true; // all locked by default (for now)
	list<Item*>::iterator it = items.begin();
	this->name = "Chest";
	this->desc = "It's an ordinary wooden chest.";
	this->type = "Interactable";
}

int Chest::open_action(Player& player) { // what the chest does when it's opened
	// return 0 loops again through INTERACT
	// return 1 goes back to EXAMINE
	// return 2 goes back to MAIN
	while (true) { // loop this while items are in the chest
		if (items.empty()) {
			cout << ">> The " << name << " is empty." << endl; // no nl bc pairs w/ other flavor text
			return 0; // loop INTERACT again
		}

		else { // list items inside
			int choice = (items.size() + 1); // cancel by default
			cout << "\nThere are items inside. What will you take?" << endl;
			for (it = items.begin(); it != items.end(); ++it) { // list items
				cout << ((distance(items.begin(), it)) + 1) << " . . . " << (*it)->name << endl;
			}
			cout << (items.size() + 1) << " . . . Take All" << endl;
			cout << (items.size() + 2) << " . . . Cancel" << endl;
			cout << "Enter choice: ";
			while (!(cin >> choice)) { // input validation
				cout << "\n>> Whoops! Try again." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Enter choice: ";
			}
			cin.clear(); // clear input buffer
			cin.ignore(10000, '\n');

			// Take All
			if (choice == (items.size() + 1)) { // add all items in chest to player backpack
				for (it = items.begin(); it != items.end(); ++it) {
					if ((*it)->name == "Key") // keys are somewhat different (don't go in backpack list)
						player.keyring++; // add to keyring
					else if ((*it)->name == "Big Key")
						player.bigkey = true;
					else player.addto_backpack(*it); // add pointer to player backpack

					if (((*it)->name == "Key") || ((*it)->name == "Big Key"))
						delete (*it); // delete key object
				}
				items.clear(); // when finished, delete all pointers from list (avoids issues with iterator and erase)

				cout << "\n>> You put all of the items into your backpack." << endl;
				// loop again
			}
			// Cancel
			else if ((choice <= 0) || (choice >= (items.size() + 2))) { // don't take anything and exit menu
				cout << "\n>> You decide not to take anything." << endl;
				return 0; // loop INTERACT again
			}
			// Item chosen
			else { // select that item and add it to player backpack
				it = items.begin();
				while ((distance(items.begin(), it) + 1) != choice) {
					++it; // iterate until it matches choice (chosen item located)
				}
				if ((*it)->name == "Key") { // keys are somewhat different (don't go in backpack list)
					player.keyring++; // add to keyring
				}
				else if ((*it)->name == "Big Key") {
					player.bigkey = true;
				}
				else {
					player.addto_backpack(*it); // add pointer to player backpack
				}

				// form output
				cout << "\n>> You put the " << (*it)->name;
				if (((*it)->name == "Key") || ((*it)->name == "Big Key")) {
					cout << " on your key ring." << endl;
					delete (*it); // delete key object (won't be used again)
				}
				else cout << " in your backpack." << endl;

				items.erase(it); // delete pointer from list
				// loop again
			}
		}
	}
}

void Chest::status() { // no new line bc pairs with other flavor text
	if (!open) cout << endl << ">> The " << name << " is closed." << endl;
	else cout << endl << ">> The " << name << " is open." << endl;
}