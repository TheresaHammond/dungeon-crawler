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
	Room* room;
	Door* door;
	int dir1;
	int dir2;
	bool validate;
	Room* next_room;
	bool finished;
	bool exit; // returns whether exit has been found by map gen or not
	int tries; // counts before map failure
	vector<int> dirs; // holds directional info that is shuffled for map gen
	vector<int>::iterator dir; // vector iterator
public:
	Map(void); // default
	Map(int size, Player& player); // constructor
	void draw_full(Player& player); // draw full map
	// void draw_player(Player& player); // draw map from player's perspective
	void door_create(Room* current, int direction, Room* next); // creates a door & places pointer to door in each connecting room
	bool room_create(Room*& current, int direction, Room* next); // creates new room in a random direction based on current room's location
	bool room_check(Room* current, int direction, Room*& next); // checks for a room in a given direction
	bool exit_search(Room* current); // looks for an exit and returns a pointer if found
};
