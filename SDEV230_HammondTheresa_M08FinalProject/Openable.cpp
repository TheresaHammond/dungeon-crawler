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

int Openable::use(Player& player) { // interaction between player and openable
	// return 0 loops again through INTERACT
	// return 1 goes back to EXAMINE
	// return 2 goes back to MAIN
	int choice;

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
			return 0; // exit this function (go back to INTERACT menu)
		}
	}
	if ((!open) && (!locked)) { // closed but not locked, will open
		cout << ">> You open the " << name << "." << endl;
		this->open = true;
	}
	if (open) // should run immediately after opening the thing
		return (open_action(player)); // might need this to return a bool?
}

int Openable::open_action(Player& player) { // what item does when it's opened
	// return TRUE goes back to MAIN
	// return FALSE loops again through INTERACT
	cout << "\n>> LOL BYE" << endl;
	return true; // exit back to MAIN
}

void Openable::status() { // no new line bc pairs with other flavor text
	if (!open) cout << ">> The " << name << " is closed." << endl;
	else cout << ">> The " << name << " is open." << endl;
}
