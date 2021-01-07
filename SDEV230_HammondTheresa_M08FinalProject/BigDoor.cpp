#include "BigDoor.h"
#include "Player.h"

#include <string>
#include <list>

using namespace std;

// inherits open_action from Door obj

BigDoor::BigDoor(void) { // def con
	// cout << "Default big door constructor!" << endl;
}

BigDoor::BigDoor(Room* current, Room* next) { // constructor!
	// cout << "New boss door constructed!" << endl;
	for (int i = 0; i < 2; i++) {
		a_rooms[i] = 0; // initialize all pointers as null
	}
	this->open = false; // boss door always closed & locked by default
	this->locked = true;
	this->name = "Big Door";
	this->desc = "A massive, gilded door. Requires an equally massive key.";
	list<string> locations{ "" }; // leave blank for now
	this->location = "nearby";
	this->a_rooms[0] = current; // insert connecting rooms to door ref
	this->a_rooms[1] = next;
	this->type = "Interactable";
}

void BigDoor::kick() {
	cout << ">> The " << name << " echoes with a heavy THUNK, but does not move." << endl;
}

int BigDoor::use(Player& player) { // interaction between player and openable
	// return 0 loops again through INTERACT
	// return 1 goes back to EXAMINE
	// return 2 goes back to MAIN
	int choice;

	if (locked) { // closed and locked, prompt to unlock it
		cout << ">> The " << dir << name << " is locked." << endl;

		// show text if player has NO keys
		if (!player.bigkey) cout << ">> You do not have a Big Key." << endl;

		// if player has a key in their inventory, prompt them to use a key
		else {
			cout << "\nWould you like to use the Big Key?" << endl;
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
				cout << "\n>> You use the Big Key to unlock the " << name << "." << endl;
				cout << ">> The Big Key sticks in the lock and is no longer usable." << endl;
				player.bigkey == false;
				this->locked = false; // unlock openable (should open automatically next)
			}
			else { // no
				cout << "\n>> You decide not to use the Big Key." << endl;
				return 0; // exit this function (go back to INTERACT menu)
			}
		}
	}
	if ((!open) && (!locked)) { // closed but not locked, will open
		cout << ">> You open the " << name << "." << endl;
		this->open = true;
	}
	if (open) // should run immediately after opening the thing
		return (open_action(player)); // might need this to return a bool?
}
