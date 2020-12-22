#include "Door.h"
#include "Player.h"

#include <string>
#include <iostream>
#include <list>

using namespace std;

Door::Door(void) { // def con
}

Door::Door(Room* current, Room* next) { // constructor!
	// cout << "New door constructed!" << endl;
	for (int i = 0; i < 2; i++) {
		a_rooms[i] = 0; // initialize all pointers as null
	}
	this->locked = true;
	this->name = "Door";
	this->desc = "It's a plain wooden door.";
	// list<string> locations{ "" }; // leave blank for now
	this->location = " nearby.";
	this->a_rooms[0] = current; // insert connecting rooms to door ref
	this->a_rooms[1] = next;
}

int Door::open_action(Player& player) { // what door does when you use it while it's open
	// return 0 loops again through INTERACT
	// return 1 goes back to EXAMINE
	// return 2 goes back to MAIN
	int choice;

	// when door is open, player has option to go through it
	cout << "\nWill you go through?" << endl;
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
		player.move2(*this); // move player to next room
		return 2; // exit INTERACT/EXAMINE and go to MAIN
	}
	else { // no
		cout << "\n>> You decide not to go through the " << dir << name << "." << endl;
		return 0; // exit this function and loop INTERACT again
	}
}

void Door::kick() {
	cout << ">> The " << name << " rattles." << endl;
}