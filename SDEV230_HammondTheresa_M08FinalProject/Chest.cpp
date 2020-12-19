#include "Chest.h"

#include <iostream>
#include <list>

using namespace std;

Chest::Chest(void) { // constructor
	this->open = false; // closed and unlocked by default
	this->locked = false;
	this->takeable = false;
	this->equippable = false;
	// this->location = "nearby";
	// this->takeable = false;
	list<Item*>::iterator it = items.begin();
	this->name = "Chest";
	this->desc = "It's an ordinary wooden chest.";
}

void Chest::use(Player& player) { // interaction between player and chest
	int choice;

	while (true) { // loop until player chooses to exit
		if (locked) { // closed and locked, prompt to unlock it
			cout << ">> The " << name << " is locked." << endl;
			// if player has a key in their inventory, prompt them to use a key
			if (player.keyring > 0) cout << "\nWould you like to use a key?" << endl;
			cout << "1 . . . Yes" << endl;
			cout << "2 . . . No" << endl;
			cout << "Enter choice: ";
			while (!(cin >> choice)) { // input validation
				cout << "\n>> Whoops! Try again." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Enter choice: ";
			}
			cin.clear(); // clear input buffer
			cin.ignore(10000, '\n');

			if (choice == 1) { // yes
				cout << "\n>> You use a key to unlock the " << name << "." << endl;
				cout << ">> The key sticks in the lock and is no longer usable." << endl;
				player.keyring--;
				this->locked = false; // unlock chest (should open automatically next)
			}
			else { // no
				cout << "\n>> You decide not to use a key." << endl;
				break; // exit this menu
			}
		}
		if ((!open) && (!locked)) { // closed but not locked, will open
			cout << ">> You open the " << name << "." << endl;
			this->open = true;
		}
		if (open) { // should run immediately after opening the chest also
			if (items.empty()) {
				cout << ">> The " << name << " is empty." << endl; // no nl bc pairs w/ other flavor text
				break;
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
				}
				// Cancel
				else if ((choice <= 0) || (choice >= (items.size() + 2))) { // don't take anything and exit menu
					cout << "\n>> You decide not to take anything." << endl;
					break; // exit this menu
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
				}
			}
		}
	}	
}

void Chest::status() { // no new line bc pairs with other flavor text
	// if (locked) cout << ">> The " << name << " is locked." << endl;
	if (!open) cout << ">> The " << name << " is closed." << endl;
	else cout << ">> The " << name << " is open." << endl;
}