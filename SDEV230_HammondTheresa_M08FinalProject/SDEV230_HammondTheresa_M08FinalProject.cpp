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

// DEFINE FUNCTIONS


// combat state!
bool state_combat(Player &player, Room &room, Entity &entity) {
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
bool state_main(Player& player, Room& room, Entity& entity) { // PASS OBJS BY REFERENCE!!!!!!!
	// if room has enemy, switch to combat state (while loop). else:
	int choice;
	bool combat = true;
	cout << "\n>> " << entity.get_name() << " attacks you!" << endl;
	while (combat) {
		combat = state_combat(player, room, entity);
	}
	if (player.get_hp() <= 0) {
		cout << "\n>> You are dead." << endl;
		return true; // game is over, you're dead
	}
	else {
		cout << "\nWhat will you do next?" << endl;
		cout << "1 . . . Look" << endl; // player.look(Room &player.location);
		cout << "2 . . . Move" << endl;
		cout << "3 . . . Open backpack" << endl; // player.open_backpack();
		cout << "4 . . . Check stats" << endl; // player.get_stats();
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) { // actions based on choice
		case 1: // Look
			// room = player.get_room();
			//cout << "\nYou look at the room around you." << endl;
			//(player.get_room()).look(); // display player room's item list
			player.look();
			break;
		case 2: // Move
			cout << "\nNot yet implemented." << endl;
			break;
		case 3: // Open backpack
			cout << "\n>> You open your backpack." << endl;
			player.open_backpack(); // open the inventory (list items)
			break;
		case 4: // Check stats
			cout << "\n>> You take stock of your current state." << endl;
			player.get_stats(); // list player stats
			break;
		default:
			cout << "\n>> You do nothing." << endl;
		}
	}
}

// MAIN
int main(void)
{
	// INITIALIZE VARIABLES
	int size = 5; // length of square grid side
	int x, y, x2, y2, random, random2;
	Room* map[5][5]; // map grid; full of pointers to Room objects!
	int* arr;
	int count = 0;
	string direction;
	string name;
	int choice;
	Item* item1; // pointer to new item created (to put in inventory)
	Item* item2;
	bool game_end = false; // flag to end game loop

	// INITIALIZE RANDOM SEED
	srand(time(NULL));

	// CREATE OBJS
	Player player;
	Room room;
	Entity entity; // enemy

	// fill backpack
	item1 = new HealthPotion; // yay polymorphism

	player.addto_backpack(item1);
	// be careful because this has HUGE POTENTIAL to create a memory leak!!


	// pregame setup (get player name, generate map)
	cout << "~~~~~ GAME NAME ~~~~~" << endl;
	cout << "\nYou have been trapped inside a dungeon and must find your way out. Good luck!" << endl;
	// get player name and set up stats
	cout << "\nPlease enter your name: ";
	getline(cin, name);
	if (name == "") {
		name = "Default Dan";
	}
	player.set_name(name);
	cout << "\n>> You are " << player.get_name() << ". Your starting stats are:" << endl;
	player.get_stats();

	cout << "\n>> You awaken in a strange new place." << endl;

	// add items to starting room
	item2 = new HealthPotion;
	room.add_item(item2); // put item in room (on floor, i guess)
	// this has to be done before passing room reference to player, because... i don't know

	player.set_room(room); // set player location inside starting room
	entity.set_room(room); // put an enemy in room (for testing)

	// describe starting room
	room.describe();

	// MAIN GAME LOOP
	while (!game_end) { // until game_end is True
		// run menu script
		game_end = state_main(player, room, entity); // open menu, pass current player reference in
	}
	// post-game stuff
	cout << "\n>> Your journey has ended." << endl;



	/* // GENERATE DUNGEON MAP

	// fill map array with room objects
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map[i][j] = new Room(); // create new room in each square
		}
	}


	// GENERATE ENTRANCE AND EXIT LOCATIONS

	// GENERATE ENTRANCE. ENTRANCE MUST BE ON EDGE! repeat until it is located on an edge space
	do {
		// generates random int between 0 and grid size
		x = rand() % size; // column coordinate
		y = rand() % size; // row coordinate
		//cout << "(" << x << ", " << y << ")" << endl;
	} while (((x != 0) && (x != size-1)) && ((y != 0) && (y != size - 1)));

	// when successful, mark that room as existing and also the entrance
	map[x][y]->is_entrance = true;
	map[x][y]->exists = true;
	map[x][y]->map_icon = "[S]";

	// GENERATE EXIT (MUST ALSO BE ON EDGE)
	// must not occupy same square as entrance!
	do {
		// generates random int between 0 and grid size
		x2 = rand() % size; // column coordinate
		y2 = rand() % size; // row coordinate
		//cout << "(" << x << ", " << y << ")" << endl;
	} while (((x2 != 0) && (x2 != size - 1)) && ((y2 != 0) && (y2 != size - 1)) && ((x2 != x) && (y2 != y)));

	// when successful, mark that room as existing and also the exit
	map[x2][y2]->is_exit = true;
	map[x2][y2]->exists = true;
	map[x2][y2]->map_icon = "[X]";

	// PATH GENERATION ALGORITHM
	// seed random rooms first
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			random = rand() % 100 + 1; // generate random number between 1 and 100
			// small chance to generate room into existence if it doesn't already exist
			if ((random < 10) && (map[i][j]->exists == false)) {
				map[i][j]->exists = true;
				map[i][j]->map_icon = "[O]";
			}
		}
	}

	// ROOM CONNECTION ALGORITHM
	// this algorithm should randomly generate a number of connected rooms for a
	// seeded room, then generate a random direction for those rooms to be in
	// relative to the seed, then create those new rooms

	for (int i = 0; i < size; i++) { // cols
		for (int j = 0; j < size; j++) { // rows
			// if room exists and has no doors, generate connecting rooms
			if ((map[i][j]->exists == true) && (map[i][j]->doors == 0)) {
				// generate random number of possible doors for room (1 to 2)
				random = rand() % 2 + 1; // this will be saved for number of actual doors
				cout << "Doors: " << random << endl;
				arr = new int[random]; // create array with size of number of doors

				// NOTE: THIS ONLY CREATES AND USES ONE ARRAY; NEED TO STORE THIS INFO
				// IN AN ARRAY UNIQUE TO EACH ROOM????
				// for each space in array, generate a random number to put in array
				// repeat random gen over and over until full of unique numbers
				while (count < random) {
					random2 = rand() % 4 + 1; // between 1 and 4, for cardinal directions
					// iterate through array to find a match of current direction
					for (int f = 0; f < random; f++) {
						if (random2 == arr[f]) break; // if match found, skip and try again
						else if (f == random - 1) { // if no match found, is not duplicate
							arr[count] = random2; // put number in array!
							count++; // increment unique number counter
						}
					}
				}
				// when this is done, print array
				for (int i = 0; i < random; i++) {
					cout << "[" << arr[i] << "]" << endl;
				}

			}

		}
	}










	cout << endl;
	// DRAW MAP
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << map[i][j]->map_icon; // draw map icon for each room!
		}
		cout << endl; // return for next row
	} */





	return 0;
}


