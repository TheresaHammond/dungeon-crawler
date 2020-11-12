#include "Player.h"
#include "Item.h"
#include "Room.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player(void) { // CONSTRUCTOR
	this->hp = 100;
	this->str = 5;
	this->def = 5;
	this->intel = 5;
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
	list<Item*> item_list = this->room.get_item_list(); // copy list of items in room
	// BACKPACK ITEM MENU LOOP
	// exit conditions: exit choice made in inner menus (last for item choice, 5 for item action)
	// NOTE: indices modified so lists display starting at 1 (instead of 0)
	// DEBUG
	cout << "Backpack size: " << backpack.size() << endl;

	while ((item_choice != (backpack.size() + 1)) && (menu_choice != 5)) {
		if (backpack.empty()) { // exits loop (closes backpack)
			cout << "\n>> Your backpack is empty." << endl;
			item_choice = 1; // forces exit condition
		}
		else {
			cout << "\nItems in backpack:" << endl; // generates enumerated list of all items currently in backpack
			for (list<Item*>::iterator it = backpack.begin(); it != backpack.end(); ++it) {
				cout << ((distance(backpack.begin(), it)) + 1) << " . . . " << (*it)->get_name() << endl; // double dereference, yay
			}
			cout << (backpack.size() + 1) << " . . . Close backpack" << endl; // show exit condition 
			cout << "Choose an item: "; // item choice prompt
			cin >> item_choice; // get player input
				// apply choice to menu item (opens item action menu)
			if (item_choice == (backpack.size() + 1)) { // if exit condition chosen
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
					cout << "\nWhat will you do with the " << (*it)->get_name() << "?" << endl; // confirm item selection
					cout << "1 . . . Examine" << endl; // (*it)->describe();, loop again
					cout << "2 . . . Use" << endl; // (*it)->use();, if single-use item, go back to item list
					cout << "3 . . . Drop" << endl; // (*it)->drop();, go back to item list
					cout << "4 . . . Pick something else" << endl; // Go back to item list
					cout << "5 . . . Cancel and close backpack" << endl; // Go back to main menu
					cout << "Enter choice: ";
					cin >> menu_choice;
					switch (menu_choice) { // actions based on choice
					case 1: // Examine
						cout << "\n>> You examine the " << (*it)->get_name() << "." << endl;
						cout << ">> [" << (*it)->get_name() << ": " << (*it)->get_desc() << "]" << endl;
						break;
					case 2: // Use
						(*it)->use();
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
						cout << "\n>> You drop the " << (*it)->get_name() << " on the floor." << endl;
						item_list.push_back(*it); // push item to room item list instead (because it's now on the floor)
						backpack.erase(it); // erase item reference from backpack
						this->room.set_item_list(item_list); // update room list from player to room
						item_choice = -1; // reset item choice (compensates for change in list size when item deleted)
						action_exit = true; // flag exit from action menu
						// DEBUG
						cout << "Backpack size: " << backpack.size() << endl;
						// cout << backpack << endl;
						break;
					case 4: // Pick something else
						cout << "\n>> You decide to choose something else." << endl;
						action_exit = true;
						break;
					case 5: // Close backpack
						cout << "\n>> You put the " << (*it)->get_name() << " back and close your backpack." << endl;
						action_exit = true;
						break;
					default:
						cout << "\n>> You do nothing." << endl;
					}
				}
			}
		}
	}
}
// INTERACT WITH ITEMS IN ROOM
void Player::look() {
	int choice = 0;
	bool look_exit = false; // break condition for look menu
	list<Item*> item_list = this->room.get_item_list(); // copy list of items in room

	while (look_exit == false) { // Keep looping through menu until exit condition reached!
		cout << "\nLook at what?" << endl;
		// first list room itself (first item in list is THIS room)
		cout << "1 . . . Room" << endl;
		// cout << "Items in room: " << item_list.size() << endl; // DEBUG
		// then list items inside room's inventory
		// ADD: only access this if have sufficient light
		for (list<Item*>::iterator it = item_list.begin(); it != item_list.end(); ++it) { // add 2 to index to compensate for room and staring at 1
			cout << ((distance(item_list.begin(), it)) + 2) << " . . . " << (*it)->get_name() << endl; // double dereference, yay
		}
		cout << (item_list.size() + 2) << " . . . Cancel" << endl; // show exit condition

		cout << "Enter choice: "; // item choice prompt
		cin >> choice; // get player input

		if (choice == 1) { // current room selected
			room.describe();
		}
		else if (choice == (item_list.size() + 2)) { // if exit condition chosen
			cout << "\n>> You decide to do something else." << endl; // nothing else happens; loops back to main menu
			look_exit = true;
		}
		else { // find item and then describe it
			list<Item*>::iterator it = item_list.begin(); // reset iterator to select item
			while (choice - 2 != (distance(item_list.begin(), it))) { // move iterator until it matches choice
				++it;
			}
			cout << "\n>> You look at the " << (*it)->get_name() << "." << endl;
			cout << ">> [" << (*it)->get_name() << ": " << (*it)->get_desc() << "]" << endl; // activate describe() method of that item
			(*it)->status(); // give more info about item's current state

			// ITEM INTERACTION LIST
			int menu_choice = 0;
			bool action_exit = false; // break condition for action menu
			while (action_exit == false) {
				cout << "\nWhat will you do with the " << (*it)->get_name() << "?" << endl;
				// iterate through and read interaction list of item
				cout << "1 . . . Use" << endl; // (*it)->use();
				cout << "2 . . . Take" << endl; // if takeable = true, (*it)->addto_backpack, delete from room list
				cout << "3 . . . Kick" << endl; // (*it)->kick(); // fun stuff
				cout << "4 . . . Look at something else" << endl; // Go back to look list
				cout << "5 . . . Stop looking" << endl; // Go back to main menu
				cout << "Enter choice: ";
				cin >> menu_choice;
				switch (menu_choice) { // actions based on choice
				case 1: // Use
					(*it)->use();
					// if single-use, delete item from list
					// item_list.erase(it);
					// update room list
					// room.set_item_list(item_list);
					action_exit = true;
					look_exit = true; // go back to main menu
					break;
				case 2: // Take
					if ((*it)->takeable == true) {
						cout << "\n>> You add the " << (*it)->get_name() << " to your backpack." << endl;
						this->addto_backpack(*it); // add item to player list
						item_list.erase(it); // delete item from room list
						this->room.set_item_list(item_list); // update room list
						action_exit = true;
						look_exit = true; // go back to main menu
					}
					else cout << "\n>> You try to take the " << (*it)->get_name() << ", but it won't budge." << endl;
					break; // loop this menu again
				case 3: // Kick
					cout << "\n>> You kick the " << (*it)->get_name() << "." << endl;
					(*it)->kick();
					break; // loop this menu again
				case 4: // Pick something else
					cout << "\n>> You decide to look at something else." << endl;
					action_exit = true; // go back to look menu
					break;
				case 5: // Stop looking
					cout << "\n>> You decide to do something else." << endl;
					action_exit = true;
					look_exit = true; // go back to main menu
					break;
				default:
					cout << "\n>> You do nothing." << endl;
				}
			}
		}
	}
}
