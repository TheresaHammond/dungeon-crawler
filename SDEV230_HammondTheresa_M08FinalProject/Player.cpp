#include "Player.h"
#include "Room.h"

#include <iostream>
#include <string>

using namespace std;

Player::Player(string name) { // constructor
	this->name = name;
	this->type = "Player";
	this->level = 1;
	this->xp = 0;
	this->maxxp = 10;
	this->hp = 20; // health points
	this->maxhp = hp;
	this->atk = 5; // strength
	this->def = 5; // defense
	this->move_count = 0; // number of times player has changed rooms
	this->keyring = 100; // number of keys player currently has
	this->bigkey = false; // whether player has big key
	this->weapon = nullptr;
	this->armor = nullptr;
}

// ADD ITEM TO BACKPACK
void Player::addto_backpack(Item* item) {
	backpack.push_front(item);
}
// BACKPACK MENU
void Player::open_backpack() {
	cout << "\n>> You open your backpack." << endl;

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

	// show amount of gems a player has
	cout << ">> You have " << gems << "gems." << endl;

	// show backpack item list
	while ((item_choice != (backpack.size() + 1)) && (menu_choice != 5)) {
		if (backpack.empty()) { // exits loop (closes backpack)
			cout << "\n>> Your backpack is empty." << endl;
			item_choice = 1; // forces exit condition
		}
		else {
			cout << "\nWhich item will you choose?" << endl; // generates enumerated list of all items currently in backpack
			for (list<Item*>::iterator it = backpack.begin(); it != backpack.end(); ++it) {
				cout << ((distance(backpack.begin(), it)) + 1) << " . . . " << (*it)->name << endl; // double dereference, yay
			}
			cout << (backpack.size() + 1) << " . . . Close backpack" << endl; // show exit condition 
			cout << "Enter choice: "; // item choice prompt
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
				break;
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
					if (((*it)->type == "Weapon") || ((*it)->type == "Armor"))
						cout << "1 . . . Equip" << endl; // equip item 
					else cout << "1 . . . Use" << endl; // (*it)->use();, if single-use item, go back to item list

					cout << "2 . . . Examine" << endl; // (*it)->describe();, loop again 
					cout << "3 . . . Drop" << endl; // (*it)->drop();, go back to item list
					cout << "4 . . . Choose something else" << endl; // Go back to item list
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
					case 1: // Use/Equip
						// EQUIP (this code sucks... wtf)
						if (((*it)->type == "Weapon") || ((*it)->type == "Armor")) {
							cout << "\n>> You decide to equip the " << (*it)->name << "." << endl;
							if ((*it)->type == "Weapon") {
								if (weapon) { // if player already has weapon equipped, store it
									cout << ">> You unequip the " << weapon << " and put it in your backpack." << endl;
									addto_backpack(this->weapon); // add pointer of current item to player's backpack
								}
								this->weapon = (*it); // replace weapon pointer with new item
							}
							else if ((*it)->type == "Armor") {
								if (armor) { // if player already has armor equipped, store it
									cout << ">> You unequip the " << armor << " and put it in your backpack." << endl;
									addto_backpack(this->armor); // add pointer of current item to player's backpack
								}
								this->armor = (*it); // replace weapon pointer with new item
							}
							backpack.erase(it); // delete item pointer from backpack
							item_choice = -1; // reset item choice (compensates for change in list size when item deleted)
							action_exit = true; // goes back to ACTION menu
							break;
						}
						// USE
						else (*it)->use(*this);

						// ADD: if single-use item, delete item from backpack and go back to item list
						/* if ((*it)->single.use = true) {
						*	backpack.erase(it);
						*	item_choice = -1;
						*	action_exit = true;
						*
						*
						* } */
						break;

					case 2: // Examine
						cout << "\n>> You examine the " << (*it)->name << "." << endl;
						(*it)->describe();
						(*it)->status();
						//cout << ">> [" << (*it)->name << ": " << (*it)->desc << "]" << endl;
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

					case 4: // Pick something else (goes back to ACTION menu)
						cout << "\n>> You decide to choose something else." << endl;
						action_exit = true;
						break;

					default: // Close backpack (goes back to MAIN menu)
						cout << "\n>> You put the " << (*it)->name  << " back and close your backpack." << endl;
						action_exit = true;
						return;
					}
				}
			}
		}
	}
}

bool Player::move_menu() { // this code is used by the MOVE option in MAIN menu

	cout << "\nUse which door?" << endl;

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
				dir = "North ";
				break;
			case 1:
				dir = "East ";
				break;
			case 2:
				dir = "South ";
				break;
			case 3:
				dir = "West ";
				break;
			}
			room->a_doors[i]->dir = dir; // update door dirs (for flavor text)
			// show menu (one entry for each door)
			cout << counter << " . . . " << dir << room->a_doors[i]->name << endl;
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
		cout << "\n>> You change your mind about using a door." << endl;
		return false;
	}
	
	counter = 0; // reusing this to find door of choice

	// look for player choice
	for (int i = 0; i < 4; i++) {
		if (room->a_doors[i]) { // if door found at that index
			counter++; // count that door (finds first available, second available, etc)
			if (counter == choice) { // door is found
				// activate use method of that door (checks whether locked, prompts to open, activates move, etc)
				room->a_doors[i]->status(); // show current status of door
				room->a_doors[i]->use(*this);
				return false; // only return true if want to end game...
			}
		}
	}
}

bool Player::move(Door& door) { // move through actual door
	for (int j = 0; j < 2; j++) {
		if (door.a_rooms[j] != room) {
			cout << "\n>> You move through the " << door.dir << door.name << "." << endl;
			room = door.a_rooms[j]; // move player to that room
			move_count++;
			if (room->get_visited()) cout << "\n>> You have been here before." << endl;
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
		list_count = 1; // set list count start
		// show doors (if they exist)
		// iterate through a_doors and if any found, show them and their location, iterate list count, and put dir values in doors
		for (int i = 0; i < 4; i++) {
			if (room->a_doors[i]) { // if door found
				string dir;
				switch (i) { // location of door
				case 0:
					dir = "North "; // space afterward for proper text fit
					break;
				case 1:
					dir = "East ";
					break;
				case 2:
					dir = "South ";
					break;
				case 3:
					dir = "West ";
					break;
				}

				room->a_doors[i]->dir = dir; // put location value in door (for flavor text)
				cout << list_count << " . . . " << room->a_doors[i]->dir << room->a_doors[i]->name << endl;
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
		}

		// if cancel not chosen, do stuff depending on what item was selected (oh my god this is a nightmare lol)
		if ((choice >= 1) && (choice <= room->door_count)) { // choice is a door, show status of that door
			// find the correct door using math lol
			int counter = choice - 1; // will use this to count down until find the nth door chosen by choice
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
		else if (choice >= room->door_count + 1) { // choice is a chest (if it exists)
			if ((room->chest) && (choice == room->door_count + 1)) {
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

bool Player::interact(Item* item, int index) { // index used for take/equip commands
	// ITEM INTERACTION LIST (from EXAMINE room or chest)
	int choice = 0;
	while (true) { // dir only not blank for doors

		cout << "\nWhat will you do with the " << item->dir << item->name << "?" << endl;

		// iterate through and read interaction list of item
		if ((item->type == "Weapon") || (item->type == "Armor"))
			cout << "1 . . . Equip" << endl; // change this menu item depending on context
		else cout << "1 . . . Use" << endl; // (*it)->use();

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
		case 1: // Use/Equip
			if ((item->type == "Weapon") || (item->type == "Armor")) {
				cout << "\n>> You decide to equip the " << item->name << "." << endl;
				if (item->type == "Weapon") { // this is kind of a mess...
					if (weapon) { // if player already has weapon equipped, store it
						cout << ">> You unequip the " << weapon << " and put it in your backpack." << endl;
						addto_backpack(this->weapon); // add pointer of current item to player's backpack
					}
					this->weapon = item; // replace weapon pointer with new item
				}
				if (item->type == "Armor") {
					if (armor) { // if player already has armor equipped, store it
						cout << ">> You unequip the " << armor << " and put it in your backpack." << endl;
						addto_backpack(this->armor); // add pointer of current item to player's backpack
					}
					this->armor = item; // replace weapon pointer with new item
				}
				
				// remove item from other host list (room)
				list<Item*>::iterator it = room->item_list.begin(); // set iterator to start
				while (index != (distance(room->item_list.begin(), it))) { // move iterator until it matches choice
					++it;
				}
				room->item_list.erase(it); // delete item pointer from room list
				return true; // go back to MAIN
			}

			else {
				cout << "\n>> You decide to use the " << item->dir << item->name << "." << endl;
				// TRUE goes back to MAIN
				// FALSE loops again through INTERACT

				switch (item->use(*this)) {
				case 0: // loop INTERACT again
					continue;
				case 1: // go back to EXAMINE
					return false;
				case 2: // go back to MAIN
					return true;
				}
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
			else cout << "\n>> You try to take the " << item->dir << item->name << ", but it won't budge." << endl;
			continue; // loop this menu again
		case 3: // Kick
			cout << "\n>> You kick the " << item->dir << item->name << "." << endl;
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

void Player::status_menu(void) { // player can look at and modify stats and equipment

	int choice;
	while (true) {
		this->get_stats(); // show player stats

		// options menu
		cout << "\nWhat would you like to do?" << endl;
		cout << "1 . . . Open backpack" << endl;
		cout << "2 . . . Unequip item(s)" << endl;
		cout << "3 . . . Do something else" << endl;
		cout << "Enter choice: ";
		while (!(cin >> choice)) {
			cout << "\n>> Whoops! Try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Enter choice: ";
		}
		cin.clear(); // clear input buffer
		cin.ignore(10000, '\n');

		switch (choice) {
		case 1: // open backpack
			open_backpack();
			break;
		case 2: // unequip
			if ((!weapon) && (!armor)) { // don't open menu if nothing to unequip
				cout << "\n>> You have nothing equipped." << endl;
				continue; // start next loop
			}
			else {
				int choice2;
				int index;

				// unequip menu
				while ((weapon) || (armor)) { // only loop while something equipped!

					index = 1;

					cout << "\nUnequip what?" << endl;

					if (weapon) {
						cout << index << " . . . Weapon" << endl;
						index++; // increment so can add more things afterward
					}
					if (armor) {
						cout << index << " . . . Armor" << endl;
						index++;
					}
					cout << index << " . . . Unequip all" << endl;
					index++;
					cout << index << " . . . Do nothing" << endl;

					cout << "Enter choice: ";
					while (!(cin >> choice2)) {
						cout << "\n>> Whoops! Try again." << endl;
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "Enter choice: ";
					}
					cin.clear(); // clear input buffer
					cin.ignore(10000, '\n');

					if ((choice2 >= index) || (choice2 < 1)) { // exit condition (max indes or below 1)
						cout << "\n>> You change your mind about unequipping." << endl;
						break; // break while loop?
					}
					else if (choice2 == (index - 1)) { // unequip all
						cout << "\n>> You unequip all of your items and put them in your backpack." << endl;
						if (weapon) {
							addto_backpack(weapon);
							weapon = nullptr;
						}
						if (armor) {
							addto_backpack(armor);
							armor = nullptr;
						}
					}
					else {
						// put item back in backpack (change flavor text to match)
						cout << "\n>> You unequip the "; // this is a HUGE mess, but it works, so...
						if (choice2 == 1) {
							if (weapon) {
								cout << weapon->name;
								addto_backpack(weapon);
								weapon = nullptr;
							}
							else {
								cout << armor->name;
								addto_backpack(armor);
								armor = nullptr;
							}
						}
						if (choice2 == 2) {
							cout << armor->name;
							addto_backpack(armor);
							armor = nullptr;
						}
						cout << " and put it in your backpack." << endl;
					}
				}
			}
			break;
		default:
			cout << "\n>> You decide to do something else." << endl;
			return; // exit to MAIN
		}
	}
}

void Player::level_up() { // check for and execute level-up!
	if (xp >= maxxp) {
		cout << "\n>> You have leveled up!" << endl;
		level++;

		// set new xp values
		int over = xp - maxxp; // calculate leftover XP
		maxxp *= 2; // double max limit for next level (fix later?)
		xp = over; // reset xp and add leftovers

		// calculate stat gain values (fix this later)
		int atkup = level + 1;
		int defup = level + 1;
		int hpup = level * 5;
		atk += atkup; // update player values
		def += defup;
		maxhp += hpup;
		hp += hpup;
		cout << ">> HP +" << hpup << endl;
		cout << ">> ATK +" << atkup << endl;
		cout << ">> DEF +" << defup << endl;
	}
}