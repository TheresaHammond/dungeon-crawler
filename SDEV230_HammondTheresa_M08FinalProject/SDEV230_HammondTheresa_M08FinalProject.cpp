// SDEV230_HammondTheresa_M08FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* Menu structure:
MAIN
	- EXAMINE
		- INTERACT
			- USE 
	MOVE
		- LOCATION


*/

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

bool yn_choice() { // basic yes/no menu

	int choice;

	cout << "\nIs this correct?" << endl;
	cout << "1 . . . Yes" << endl;
	cout << "2 . . . No" << endl;

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
	case 1: // yes
		return true;
	default: // no
		return false;
	}
}

// combat state!
bool state_combat(Player &player, Entity &enemy) {
	int choice;
	int damage;

	// drops
	int gems;
	int keys;
	int xp;

	// SHOW BATTLE STATS
	cout << "\n>> " << player.get_name() << ": " << player.get_hp() << "/" << player.get_maxhp() << " HP" << endl; // player
	// show for each enemy (when multiple are implemented)
	cout << ">> " << enemy.get_name() << ": " << enemy.get_hp() << "/" << enemy.get_maxhp() << " HP" << endl; // enemy

	// PLAYER ACTION MENU
	cout << "\nWhat's your next move?" << endl;
	cout << "1 . . . Attack" << endl; // attack enemy
	cout << "2 . . . Defend" << endl; // defend from attack
	cout << "3 . . . Open backpack" << endl; // player.open_backpack();
	cout << "4 . . . Use spell" << endl; // open spellbook
	cout << "5 . . . Talk" << endl; // attempt to communicate
	cout << "6 . . . Run" << endl; // go back to previous room (if possible)
	cout << "Enter choice: ";
	while (!(cin >> choice)) {
		cout << "\n>> Whoops! Try again." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter choice: ";
	}
	cin.clear(); // clear input buffer
	cin.ignore(10000, '\n');

	switch (choice) { // actions based on choice
		case 1: // Attack
			player.attack(enemy);
			break;
		case 2: // Defend
			cout << "\n>> Not yet implemented." << endl;
			break;
		case 3: // Open backpack
			cout << "\n>> Not yet implemented." << endl;
			// cout << "\n>> You open your backpack." << endl;
			// player.open_backpack(); // open the inventory (list items)
			break;
		case 4: // Use spell
			cout << "\n>> Not yet implemented." << endl;
			break;
		case 5: // Talk
			cout << "\n>> Not yet implemented." << endl;
			break;
		case 6: // Run
			cout << "\n>> Not yet implemented." << endl;
			// cout << ">> You escape to the previous room." << endl;
			// return false; // leave combat state
			break;
		default:
			cout << "\n>> You do nothing." << endl;
	}

	// BATTLE END CHECK 1 (all enemies defeated)
	if (enemy.get_hp() <= 0) {
		cout << "\n>> Enemy " << enemy.get_name() << " dies." << endl;

		// if all enemies have been defeated
		cout << "\n>> You are victorious!" << endl;

		// transfer enemy XP to player
		cout << ">> You gain " << enemy.get_xp() << " XP." << endl;
		player.set_xp(player.get_xp() + enemy.get_xp());
		player.level_up(); // check for level-up

		// transfer enemy items to drop obj in room

		delete &enemy; // delete enemy

		return false; // leave combat state
	}

	// ENEMY ACTION (expand later w/ choice)
	enemy.attack(player);

	// BATTLE END CHECK 2 (player defeated)
	if (player.get_hp() <= 0) {
		cout << "\n>> You are dead." << endl;
		return false; // leave combat state
	}
	else return true; // continue loop
}

// main menu function!
bool state_main(Player& player, Map& map) { // PASS OBJS BY REFERENCE!!!!!!

	Room*& room = (player.get_room()); // this should return a reference instead of a copy... hopefully...
	Entity*& enemy = (room->get_enemy());

	// if current room has enemy, switch to combat state! ends when either enemy or player dies
	if (enemy) {
		bool combat = true;
		cout << "\n>> A stray " << enemy->get_name() << " attacks you!" << endl; // could use some variations here
		while (combat) { // remains true until combat ends (returns false)
			combat = state_combat(player, *enemy); // what is going on with the references here?
		}
		// check if player still alive
		if (player.get_hp() <= 0) {
			return true; // game is over, you're dead
		}
		else enemy = nullptr; // fix dangling pointer after enemy deletion
	}

	// reiterate room description every time menu renews (combat takes priority)
	// if room is new, set room as visited (so it describes as new only on first visit)
	room->describe(); 
	if (!(room->get_visited())) room->set_visited();

	int choice;

		if (debg) cout << "You are in room (" << (player.get_room())->get_x() << ", " << (player.get_room())->get_y() << ")" << endl;
		cout << "\nWhat will you do next?" << endl;
		cout << "1 . . . Examine items" << endl; // 
		cout << "2 . . . Use door" << endl;
		cout << "3 . . . Open backpack" << endl;
		cout << "4 . . . View map" << endl;
		cout << "5 . . . Check status" << endl; 
		cout << "Enter choice: ";
		while (!(cin >> choice)) {
			cout << "\n>> Whoops! Try again." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Enter choice: ";
		}
		cin.clear(); // clear input buffer
		cin.ignore(10000, '\n');

		switch (choice) { // actions based on choice
		case 1: // EXAMINE (Can open doors and chests)
			player.examine();
			return false; // break loop, loop again
		case 2: // MOVE (a faster way to move through doors than Examine)
			player.move_menu();
			if ((player.get_room())->is_an_exit())
				return true; // break loop and end game if player is in exit room (temp solution)
			else return false;
		case 3: // OPEN BACKPACK (Check inventory)
			player.open_backpack(); // open the inventory (list of items)
			return false;
		case 4: // CHECK MAP (Draws map)
			cout << "\n>> You open your map." << endl;
			map.draw_full(player);
			return false;
		case 5: // CHECK SELF (Shows player info)
			cout << "\n>> You take stock of your current state." << endl;
			player.status_menu();
			return false;
		default:
			cout << "\n>> You decide to do nothing." << endl;
			return false;
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
	cout << "~~~~~ DUNGEON EXPLORER GAME (ALPHA) ~~~~~" << endl;
	cout << "\nYou have been trapped inside a dungeon and must find your way out. Good luck!" << endl;
	cout << "\nSelect dungeon size: " << endl;
	cout << "1 . . . Small" << endl;
	cout << "2 . . . Medium" << endl;
	cout << "3 . . . Large" << endl;
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
	cout << "\nWhat is your name?" << endl;
	cout << "Enter name: ";
	cin >> name;
	if (name == "") name = "Default Dan";
	cout << "\n>> You are " << name << "." << endl;

	string background; // used in following menu
	
	// get player background
	while (true) {
	cout << "\nWho are you?" << endl;
	cout << "1 . . . Knight" << endl;
	cout << "2 . . . Explorer" << endl;
	cout << "3 . . . Sacrifice" << endl;
	cout << "Enter choice: ";
	while (!(cin >> choice)) { // input validation
		cout << "\n>> Whoops! Try again." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter choice: ";
	}
	cin.clear(); // clear input buffer
	cin.ignore(10000, '\n');
	
	switch (choice) {
		case 1: // knight
			cout << "\n>> [Knight]: (Background)" << endl;
			cout << ">> You are a hero, come to slay the evil being in the dungeon depths." << endl;
			background = "Knight";
			break; // break out of switch but NOT while loop
		case 2: // explorer
			cout << "\n>> [Explorer]: (Background)" << endl;
			cout << ">> You are a scholar, come to learn about the fabled mysteries of the deep." << endl;
			background = "Explorer";
			break;
		case 3: // sacrifice
			cout << "\n>> [Sacrifice]: (Background)" << endl;
			cout << ">> You are a sacrifice to appease the dungeon's great evil, abandoned here to die." << endl;
			background = "Sacrifice";
			break;
		default: // out of range
			cout << "\n>> You must make a choice." << endl;
			continue; // will start menu again and NOT go to y/n menu
		}

	if (yn_choice()) break; // if confirmed yes, break out of while loop
	}

	// CREATE OBJS
	// player obj
	Player player(name, background);

	// generate map and set player in starting room
	Map map(map_size, player, debg);

	// show map (DEBUG)
	if (debg) map.draw_full(player);

	cout << "\n>> You awaken in a strange new place." << endl;

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


