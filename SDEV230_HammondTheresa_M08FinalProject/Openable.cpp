#include "Openable.h"
#include "Player.h"

#include <iostream>
#include <list>

using namespace std;

Openable::Openable(void) { // constructor
	this->open = false; // closed and unlocked by default
	this->locked = false;
	this->takeable = false;
	this->equippable = false;
}

void Openable::use(Player& player) { // interaction between player and openable
	int choice;
	bool breakloop = false;

	while (!breakloop) { // loop until player chooses to exit
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
				this->locked = false; // unlock openable (should open automatically next)
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
		if (open) // should run immediately after opening the thing
			breakloop = open_action(player);
	}
}

bool Openable::open_action(Player& player) { // what item does when it's opened
	cout << "\n>> LOL BYE" << endl;
	return true; // leave while loop
}

void Openable::status() { // no new line bc pairs with other flavor text
	if (!open) cout << ">> The " << name << " is closed." << endl;
	else cout << ">> The " << name << " is open." << endl;
}
