// SDEV230_HammondTheresa_M08FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <time.h>
#include <list>
// yeehaw look at all these classes
#include "Item.h"
#include "Door.h"
#include "Room.h"
#include "Entity.h"
#include "Player.h"
#include "HealthPotion.h"
#include "Map.h"

using namespace std;

// GLOBAL VARS
bool debg = false; // debug flag

// DEFINE FUNCTIONS
// combat state!
bool state_combat(Player &player, Room* room, Entity &entity) {
	int choice;
	int damage = 0;
	if (player.get_hp() <= 0) { // you died
		return false; // leave combat state
	} else if (entity.get_hp() <= 0) {
		cout << "\n>> Enemy " << entity.get_name() << " has been defeated!" << endl;
		// run post-combat stuff
		return false; // leave combat state
	} else {
		cout << "\nWhat's your next move?" << endl;
		cout << "1 . . . Attack" << endl; // attack enemy
		cout << "2 . . . Defend" << endl; // defend from attack
		cout << "3 . . . Open backpack" << endl; // player.open_backpack();
		cout << "4 . . . Use spell" << endl; // open spellbook
		cout << "5 . . . Talk" << endl; // attempt to communicate
		cout << "6 . . . Run" << endl; // go back to previous room (if possible)
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) { // actions based on choice
		case 1: // Attack
			cout << "\n>> You attack the " << entity.get_name() << "!" << endl;
			// calculate damage
			damage = 30; // change this later
			if (damage < 0) damage = 0; // prevent negative numbers
			cout << ">> The enemy " << entity.get_name() << " takes " << damage << " damage." << endl;
			entity.set_hp(damage);
			break;
		case 2: // Defend
			cout << "\n>> Not yet implemented." << endl;
			break;
		case 3: // Open backpack
			cout << "\n>> You open your backpack." << endl;
			player.open_backpack(); // open the inventory (list items)
			break;
		case 4: // Use spell
			cout << "\n>> Not yet implemented." << endl;
			break;
		case 5: // Talk
			cout << "\n>> Not yet implemented." << endl;
			break;
		case 6: // Run
			cout << "\n>> You attempt to flee!" << endl;
			cout << ">> You escape to the previous room." << endl;
			return false; // leave combat state
			break;
		default:
			cout << "\n>> You do nothing." << endl;
		}

		// ENEMY ATTACK ALGORITHM HERE!
		cout << "\n>> Enemy " << entity.get_name() << " attacks!" << endl;
		damage = 10; // change this later
		if (damage < 0) damage = 0; // prevent negative numbers
		cout << ">> You take " << damage << " damage." << endl;
		player.set_hp(damage);
	}
}

// main menu function!
bool state_main(Player& player, Map& map) { // PASS OBJS BY REFERENCE!!!!!!!
	// if player's room has enemy, switch to combat state (while loop). else:
	int choice;
	/* bool combat = true;
	cout << "\n>> " << entity.get_name() << " attacks you!" << endl;
	while (combat) {
		combat = state_combat(player, entity);
	}
	if (player.get_hp() <= 0) {
		cout << "\n>> You are dead." << endl;
		return true; // game is over, you're dead
	}
	else { */
	cout << "DEBUG: You are in room (" << (player.get_room())->get_x() << ", " << (player.get_room())->get_y() << ")" << endl;
		cout << "\nWhat will you do next?" << endl;
		cout << "1 . . . Look" << endl; // 
		cout << "2 . . . Move" << endl;
		cout << "3 . . . Open backpack" << endl;
		cout << "4 . . . Check map" << endl;
		cout << "5 . . . Check stats" << endl; 
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) { // actions based on choice
		case 1: // Look
			player.look();
			return false; // break loop, loop again
		case 2: // Move
			// cout << "\nNot yet implemented." << endl;
			player.move();
			return false;
		case 3: // Open backpack
			cout << "\n>> You open your backpack." << endl;
			player.open_backpack(); // open the inventory (list of items)
			return false;
		case 4: // Check map
			cout << "\n>> You open your map." << endl;
			map.draw_full(player);
			return false;
		case 5: // Check stats
			cout << "\n>> You take stock of your current state." << endl;
			player.get_stats(); // list player stats
			return false;
		default:
			cout << "\n>> You decide to do nothing." << endl;
			return false;
		//}
	}
}

// MAIN
int main(void)
{
	// INITIALIZE VARIABLES
	string name;
	int choice;
	int map_size; // changes based on difficulty
	Item* item1; // pointer to new item created (to put in inventory)
	Item* item2;
	bool game_end = false; // flag to end game loop
	int move_count = 0; // counts number of times player has changed rooms

	// INITIALIZE RANDOM SEED
	srand(time(NULL));

	// pregame setup
	cout << "~~~~~ DUNGEON GAME ~~~~~" << endl;
	cout << "\nYou have been trapped inside a dungeon and must find your way out. Good luck!" << endl;
	cout << "\nSelect dungeon size: " << endl;
	cout << "1 . . . Small" << endl;
	cout << "2 . . . Medium" << endl;
	cout << "3 . . . Large" << endl;
	cout << "Enter choice: ";
	cin >> choice;

	switch (choice) {
	case 2: // small
		cout << "\n>> Medium dungeon selected." << endl;
		map_size = 5;
		break;
	case 3: // large
		cout << "\n>> Large dungeon selected." << endl;
		map_size = 6;
		break;
	default: // default to small
		cout << "\n>> Small dungeon selected." << endl;
		map_size = 4;
	}

	// get player name
	cout << "\nPlease enter your name: ";
	cin >> name;
	if (name == "") name = "Default Dan";
	cout << "\n>> You are " << name << "." << endl;

	// CREATE OBJS
	// player obj
	Player player(name);

	// generate map and set player in starting room
	Map map(map_size, player, debg);

	// show map (DEBUG)
	if (debg) map.draw_full(player);

	cout << "\n>> You awaken in a strange new place." << endl;

	// describe starting room
	(player.get_room())->describe();
	// set starting room as visited (set after so it describes as new)
	(player.get_room())->set_visited();

	// "What will you do next?"

	// MAIN GAME LOOP
	while (!game_end) { // until game_end is True
		// run menu script
		game_end = state_main(player, map); // open menu, pass current player reference in
	}
	// post-game stuff
	cout << "\n>> Your journey has ended." << endl;

	// scoring output goes here

	return 0;
}


