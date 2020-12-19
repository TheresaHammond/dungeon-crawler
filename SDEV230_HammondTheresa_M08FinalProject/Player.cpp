#include "Player.h"
#include "Room.h"

#include <iostream>
#include <string>

using namespace std;

Player::Player(string name) { // constructor
	this->name = name;
	this->hp = 100; // health points
	this->str = 5; // strength
	this->def = 5; // defense
	this->intel = 5; // intelligence
	this->move_count = 0; // number of times player has changed rooms
	this->keyring = 1; // number of keys player currently has
	this->bigkey = false; // whether player has big key
}

// ADD ITEM TO BACKPACK
void Player::addto_backpack(Item* item) {
	backpack.push_front(item);
}
// BACKPACK MENU
void Player::open_backpack() {
	// enumerate and print list of items in backpack
	int item_choice = -1; // initialize
	int menu_choice = 0;
	bool action_exit = false; // flag to leave item action menu
	// BACKPACK ITEM MENU LOOP
	// exit conditions: exit choice made in inner menus (last for item choice, 5 for item action)
	// NOTE: indices modified so lists display starting at 1 (instead of 0)

	// cout << "Backpack size: " << backpack.size() << endl; // DEBUG

	// show amount of keys player has (before item list) (this is one sentence)
	cout << "\n>> You have " << keyring;
	if (keyring == 1) cout << " key";
	else cout << " keys";
	if (bigkey) cout << " and a Big Key";
	cout << " on your key ring." << endl;

	// show backpack item list
	while ((item_choice != (backpack.size() + 1)) && (menu_choice != 5)) {
		if (backpack.empty()) { // exits loop (closes backpack)
			cout << "\n>> Your backpack is empty." << endl;
			item_choice = 1; // forces exit condition
		}
		else {
			cout << "\nItems in backpack:" << endl; // generates enumerated list of all items currently in backpack
			for (list<Item*>::iterator it = backpack.begin(); it != backpack.end(); ++it) {
				cout << ((distance(backpack.begin(), it)) + 1) << " . . . " << (*it)->name << endl; // double dereference, yay
			}
			cout << (backpack.size() + 1) << " . . . Close backpack" << endl; // show exit condition 
			cout << "Choose an item: "; // item choice prompt
			// get player input
			while (!(cin >> item_choice)) { // input validation
				cout << "\n>> Whoops! Try again." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Enter choice: ";
			}
			cin.clear(); // clear input buffer
			cin.ignore(10000, '\n');

				// apply choice to menu item (opens item action menu)
			if ((item_choice > backpack.size()) || (item_choice < 1)) { // if exit condition chosen
				cout << "\n>> You close your backpack." << endl; // nothing else happens; loops back to main menu
			}
			else { // ITEM ACTION MENU LOOP
				list<Item*>::iterator it = backpack.begin(); // reset iterator to select item
				while (item_choice - 1 != (distance(backpack.begin(), it))) { // move iterator until it matches choice
					++it;
				}
				menu_choice = 0; // reset
				action_exit = false;
				while (!action_exit) { // only loop menu when examine/use chosen (everything else exits loop)
					cout << "\nWhat will you do with the " << (*it)->name << "?" << endl; // confirm item selection
					cout << "1 . . . Examine" << endl; // (*it)->describe();, loop again
					cout << "2 . . . Use" << endl; // (*it)->use();, if single-use item, go back to item list
					cout << "3 . . . Drop" << endl; // (*it)->drop();, go back to item list
					cout << "4 . . . Pick something else" << endl; // Go back to item list
					cout << "5 . . . Cancel and close backpack" << endl; // Go back to main menu
					cout << "Enter choice: ";
					while (!(cin >> menu_choice)) { // input validation
						cout << "\n>> Whoops! Try again." << endl;
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Enter choice: ";
					}
					cin.clear(); // clear input buffer
					cin.ignore(10000, '\n');

					switch (menu_choice) { // actions based on choice
					case 1: // Examine
						cout << "\n>> You examine the " << (*it)->name << "." << endl;
						(*it)->describe();
						(*it)->status();
						//cout << ">> [" << (*it)->name << ": " << (*it)->desc << "]" << endl;
						break;
					case 2: // Use
						(*it)->use(*this); 
						// ADD: if single-use item, delete item from backpack and go back to item list
						/* if ((*it)->single.use = true) {
						*	backpack.erase(it);
						*	item_choice = -1;
						*	action_exit = true;
						*
						*
						* } */
						break;
					case 3: // Drop
						cout << "\n>> You drop the " << (*it)->name << " on the floor." << endl;
						room->item_list.push_back(*it); // push item to room item list instead (because it's now on the floor)
						backpack.erase(it); // erase item reference from backpack
						item_choice = -1; // reset item choice (compensates for change in list size when item deleted)
						action_exit = true; // flag exit from action menu
						// cout << "Backpack size: " << backpack.size() << endl; // DEBUG
						// cout << backpack << endl;
						break;
					case 4: // Pick something else
						cout << "\n>> You decide to choose something else." << endl;
						action_exit = true;
						break;
					case 5: // Close backpack
						cout << "\n>> You put the " << (*it)->name  << " back and close your backpack." << endl;
						action_exit = true;
						break;
					default:
						cout << "\n>> You decide to do nothing." << endl;
						action_exit = true;
						break;
					}
				}
			}
		}
	}
}

bool Player::move() { // this code is used by the MOVE option (main menu)
	cout << "\nMove where?" << endl;

	string dir;
	int choice = 2; // 2 is default cancel bc rooms always have at least 1 door
	int counter = 1; // counts doors found (starts at 1 for same reason as above)

	// cout << "Doors in room: " << room->door_count << endl; // DEBUG

	// draw door menu based on current doors in room
	for (int i = 0; i < 4; i++) {
		// show only if there is a door in that array index
		if (room->a_doors[i]) {
			// get directional value based on door index
			switch (i) {
			case 0:
				dir = "North";
				break;
			case 1:
				dir = "East";
				break;
			case 2:
				dir = "South";
				break;
			case 3:
				dir = "West";
				break;
			}
			// show menu (one entry for each door)
			cout << counter << " . . . " << dir << " door" << endl;
			counter++;
		}
	}
	// show cancel option (end of menu)
	cout << counter << " . . . Cancel" << endl;
	// get player choice
	cout << "Enter choice: ";
	while (!(cin >> choice)) { // input validation
		cout << "\n>> Whoops! Try again." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter choice: ";
	}
	cin.clear(); // clear input buffer
	cin.ignore(10000, '\n');

	if ((choice >= counter) || (choice < 1)) { // player chooses cancel
		cout << "\n>> You change your mind about moving." << endl;
		return false;
	}
	
	counter = 0; // reusing this to find door of choice

	// look for player choice
	for (int i = 0; i < 4; i++) {
		if (room->a_doors[i]) { // if door found at that index
			counter++; // count that door (finds first available, second available, etc)
			if (counter == choice) {
				// check whether door is locked
				if (room->a_doors[i]->locked) {
					cout << "\n>> Door is locked and requires a key." << endl;
					return false;
				}
				else {
					// look for adjacent room inside door (that doesn't match current room)
					for (int j = 0; j < 2; j++) {
						if (room->a_doors[i]->a_rooms[j] != room) {
							cout << "\n>> You move through the door." << endl;
							room = room->a_doors[i]->a_rooms[j]; // move player to that room
							room->describe(); // tell us about the new room
							if (room->visited) cout << "\n>> You have been here before." << endl;
							if (!room->visited) room->visited = true; // mark room as visited if it hasn't been
							move_count++;
							if (room->is_exit) return true; // return true only if player's is now in exit
							else return false;
							// potential combat activation here???
						}
					}
				}
			}
		}
	}
}

bool Player::move2(Door& door) { // this code is used by the INTERACT menu when using doors
	for (int j = 0; j < 2; j++) {
		if (door.a_rooms[j] != room) {
			cout << "\n>> You move through the door." << endl;
			room = door.a_rooms[j]; // move player to that room
			room->describe(); // tell us about the new room
			if (room->visited) cout << "\n>> You have been here before." << endl;
			if (!room->visited) room->visited = true; // mark room as visited if it hasn't been
			move_count++;
			if (room->is_exit) return true; // return true only if player's is now in exit
			else return false;
			// potential combat activation here???
		}
	}
}

// INTERACT WITH ITEMS IN ROOM
void Player::examine() {
	int choice = 0;
	bool look_exit = false; // break condition for look menu
	list<Item*>::iterator it = room->item_list.begin();
	int list_count = 0; // pushes cancel option to end of list depending on doors & chest existence

	while (!look_exit) { // keep looping while look_exit is false
		cout << "\nExamine what?" << endl;
		// first list room itself (first item in list is THIS room)
		// cout << "Items in room: " << item_list.size() << endl; // DEBUG

		// then list items inside room's inventory
		// ADD: only access this if have sufficient light

		// DRAW LOOK LIST
		cout << "1 . . . Room" << endl; // look at the room itself (always at 1)
		list_count = 2; // set list count start
		// show doors (if they exist)
		// iterate through a_doors and if any found, show them and their location and iterate list count
		for (int i = 0; i < 4; i++) {
			if (room->a_doors[i]) {
				string dir;
				switch (i) { // location of door
				case 0:
					dir = "North";
					break;
				case 1:
					dir = "East";
					break;
				case 2:
					dir = "South";
					break;
				case 3:
					dir = "West";
					break;
				}
				cout << list_count << " . . . " << dir << " Door" << endl;
				list_count++; // increment to push cancel option to end of list
			}
		}
		if (room->chest) { // show chest (if it exists)
			cout << list_count << " . . . Chest" << endl;
			list_count++;
		}
		if (!room->item_list.empty()) { // show items (if there are any)
			for (list<Item*>::iterator it = room->item_list.begin(); it != room->item_list.end(); ++it) {
				cout << ((distance(room->item_list.begin(), it)) + list_count) << " . . . " << (*it)->name << endl;
			}
		}
		cout << (room->item_list.size() + list_count) << " . . . Cancel" << endl; // show exit condition (always at the end)

		// GET PLAYER CHOICE
		cout << "Enter choice: "; // item choice prompt
		// get player input
		while (!(cin >> choice)) { // input validation
			cout << "\n>> Whoops! Try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Enter choice: ";
		}
		cin.clear(); // clear input buffer
		cin.ignore(10000, '\n');

		// cancel if option chosen, or choice out of scope
		if ((choice >= (room->item_list.size() + list_count)) || (choice < 1)) {
			cout << "\n>> You decide to do something else." << endl; // nothing else happens; loops back to main menu
			break;
			//look_exit = true;
			//continue;
		}

		// if cancel not chosen, do stuff depending on what item was selected (oh my god this is a nightmare lol)
		if (choice == 1) { // current room selected
			room->describe();
			// stay inside loop
		}
		else if ((choice >= 2) && (choice <= room->door_count + 1)) { // choice is a door, show status of that door
			// find the correct door using math lol
			int counter = choice - 2; // will use this to count down until find the nth door chosen by choice
			for (int d = 0; d < 4; d++) { // iterate through possible doors in room
				if (room->a_doors[d]) // if door exists
					if (counter == 0) {
						room->a_doors[d]->describe(); // show info about door
						room->a_doors[d]->status(); 
						look_exit = interact(room->a_doors[d], 0); // start interaction menu
						break; // break for loop
					}
					else counter--; // decrement counter			
			}
		}
		else if (choice >= room->door_count + 2) { // choice is a chest (if it exists)
			if ((room->chest) && (choice == room->door_count + 2)) {
				room->chest->describe(); // show info about chest
				room->chest->status();
				look_exit = interact(room->chest, 0); // start interaction menu
				// interact returns true if we want to go straight back to the main menu
				continue;
			}
			if (!room->item_list.empty()) { // choice is an item scattered in room
				list<Item*>::iterator it = room->item_list.begin(); // reset iterator to select item
				while (choice != (distance(room->item_list.begin(), it) + list_count)) { // move iterator until it matches choice
					++it;
				}
				(*it)->describe();  // show info about item
				(*it)->status();
				look_exit = interact(*it, distance(room->item_list.begin(), it)); // start interaction menu
				// interact returns true if we want to go straight back to the main menu
			}
		}
	}
}

bool Player::interact(Item* item, int index) { // index used for take command (if takeable)
	// ITEM INTERACTION LIST
	int choice = 0;
	while (true) {
		cout << "\nWhat will you do with the " << item->name << "?" << endl;
		// iterate through and read interaction list of item
		cout << "1 . . . Use" << endl; // (*it)->use();
		cout << "2 . . . Take" << endl; // if takeable = true, (*it)->addto_backpack, delete from room list
		cout << "3 . . . Kick" << endl; // (*it)->kick(); // fun stuff
		cout << "4 . . . Look at something else" << endl; // Go back to look list
		cout << "5 . . . Stop looking" << endl; // Go back to main menu
		cout << "Enter choice: ";
		while (!(cin >> choice)) { // input validation
			cout << "\n>> Whoops! Try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Enter choice: ";
		}
		cin.clear(); // clear input buffer
		cin.ignore(10000, '\n');

		switch (choice) { // actions based on choice
		case 1: // Use
			cout << "\n>> You decide to use the " << item->name << "." << endl;
			// TRUE goes back to MAIN
			// FALSE loops again through INTERACT
\
			switch (item->use(*this)) {
			case 0: // loop INTERACT again
				continue;
			case 1: // go back to EXAMINE
				return false;
			case 2: // go back to MAIN
				return true;
			}
		case 2: // Take
			if (item->takeable == true) {
				cout << "\n>> You add the " << item->name << " to your backpack." << endl;
				this->addto_backpack(item); // add item to player list
				list<Item*>::iterator it = room->item_list.begin(); // set iterator to start
				while (index != (distance(room->item_list.begin(), it))) { // move iterator until it matches choice
					++it;
				}
				room->item_list.erase(it); // delete item pointer from room list
				return true; // go back to MAIN menu (not EXAMINE menu)
			}
			else cout << "\n>> You try to take the " << item->name << ", but it won't budge." << endl;
			continue; // loop this menu again
		case 3: // Kick
			cout << "\n>> You kick the " << item->name << "." << endl;
			item->kick();
			continue; // loop this menu again
		case 4: // Pick something else
			cout << "\n>> You decide to look at something else." << endl;
			return false; // leave this function and go back to EXAMINE menu
		default: // Stop looking (also case 5)
			cout << "\n>> You decide to do something else." << endl;
			return true; // go back to MAIN menu
		// default:
			// cout << "\n>> You decide to do nothing." << endl;
		}
	}
}