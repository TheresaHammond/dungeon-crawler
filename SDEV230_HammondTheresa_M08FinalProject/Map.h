#pragma once

#include "Room.h"
#include "Door.h"
#include "BigDoor.h"
#include "Player.h"
#include <vector>

class Map { // the dungeon map
private:
	int size;
	Room*** map; // actual map array
	Room* start; // starting room
	bool finished;
	Door* door;
	int iteration; // level of path gen (0 for main, ++ for each branch pass)
	bool complete; // whether map gen has finished successfully or not
	vector<Door*> v_doors;
	vector<Door*>::iterator dsit;
	bool debg; // debug flag
public:
	Map(void); // default
	Map(int size, Player& player, bool debg); // constructor
	void draw_full(Player& player); // draw full map
	// void draw_player(Player& player); // draw map from player's perspective
	void path_start(Player& player, Room*& start, Room*& current); // creates map entrance and exit;
	bool path_gen(Room*& current); // generates paths in map
	void path_erase(Room* start, Room*& current); // erases main path (all rooms & doors) if exit not connected
	void door_create(Room* current, int direction, Room* next); // creates a door & places pointer to door in each connecting room
	bool room_create(Room*& current, int direction, Room* next, int iteration); // creates new room in a random direction based on current room's location
	bool room_check(Room* current, int direction, Room*& next); // checks for a room in a given direction
};
