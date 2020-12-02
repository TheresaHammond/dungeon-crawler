#include "Map.h"
#include <algorithm> // for random_shuffle()

using namespace std;

Map::Map(int size, Player& player) { // CONSTRUCTOR (generates entire map!)
	cout << "\n>> Generating dungeon..." << endl;
	int x;
	int y;
	this->size = size;
	this->validate = false;
	Room* start = nullptr;
	Room* current = nullptr;
	Room* next = nullptr;
	bool exit = false;
	bool finished = false;
	int tries = 0;
	int direction;
	vector<int> v_dirs = { 0, 1, 2, 3 }; // directional info (gets shuffled)
	vector<int>::iterator dit = dirs.begin(); // iterator for directional vector 
	
	// generate a 2-dimensional square grid array using size parameter
	map = new Room * *[size];
	for (int i = 0; i < size; i++) {
		map[i] = new Room * [size] {0}; // initialize all pointers as null
	}

	// GENERATE ENTRANCE (along map edge)
	do { // generate random int within grid params
		x = rand() % size; // column coordinate
		y = rand() % size; // row coordinate
		//cout << "(" << x << ", " << y << ")" << endl;
	} while (((x != 0) && (x != size - 1)) && ((y != 0) && (y != size - 1)));

	// create & initialize entrance room
	map[x][y] = new Room(x, y);
	start = map[x][y];
	start->is_entrance = true;
	start->map_icon = "[S]";
	cout << "ENTRANCE: " << x << ", " << y << endl; // debug

	// put player in entrance room
	player.room = start;

	// set start as first room for map gen
	current = start;

	// GENERATE EXIT (also along map edge); CANNOT BE SAME SPACE AS ENTRANCE
	while (true) {
		// generate random int within grid params
		x = rand() % size; // column coordinate
		y = rand() % size; // row coordinate
		if (((x != 0) && (x != size - 1)) && ((y != 0) && (y != size - 1)))
			if (!map[x][y]) break; // break loop if map space is empty (free)!
	}
	/* do { // generate random int within grid params
		x = rand() % size; // column coordinate
		y = rand() % size; // row coordinate
		// do not allow entrance and exit to be in the same location! (this doesn't always work... fix it)
	} while (((x != 0) && (x != size - 1)) && ((y != 0) && (y != size - 1)) && (map[x][y])); */

	// create exit room
	map[x][y] = new Room(x, y);
	map[x][y]->is_exit = true;
	map[x][y]->map_icon = "[E]";
	cout << "EXIT: " << x << ", " << y << endl; // debug

	// check for a room in a random direction (allows for more random directional movement)
	// takes an array of ints 0-3 and shuffles them randomly for every room, then reads them all for search
	direction = *(v_dirs.begin()); // get first element of dirs

	// BEGIN PATH GENERATION LOOP
	// while (!finished) {
	for (int m = 0; m < 15; m++) {
		// shuffle directions
		random_shuffle(v_dirs.begin(), v_dirs.end());
		// set iterator to first element of vector
		dit = v_dirs.begin();

		// loops back here every time new room created
		// get current room coordinates
		x = current->x;
		y = current->y;

		// reset flag for successful room creation
		bool room_created = false;

		cout << "CURRENT ROOM: (" << x << ", " << y << ")" << endl; // DEBUG

		// look for exit anywhere around current room; if true, break, path gen is finished
		for (int d = 0; d < 4; d++) {
			// returns true if room found
			cout << "EXIT LOOK DIR: " << d << endl; // DEBUG
			if (room_check(current, d, next)) {
				if (next != nullptr) {
					// if the room found is and exit, create a Big Door connection and quit map generation
					if (next->is_exit) {
						door_create(current, d, next);
						cout << "EXIT FOUND AND CONNECTED. COMPLETE." << endl;
						return;
					}
					else cout << "ROOM FOUND, BUT IS NOT EXIT." << endl; // DEBUG
				}
				else cout << "ROOM NOT FOUND. TRYING ANOTHER DIRECTION..." << endl;
			} 
			// out of bounds
		}
		cout << "EXIT NOT FOUND. CONTINUING GENERATION..." << endl;

		// loop for directional search. if first element can't create a room, move to next element until either found, or error
		while ((dit != v_dirs.end()) || (!room_created)) {
			// get vector element at current iterator location
			direction = *dit;

			cout << "LOOK DIR: " << direction << endl; // debug

			// check for room in direction
			// if room_check is FALSE, then there is no room there... create one

			if (room_create(current, direction, next)) {
				room_created = true;
				break; // break inner while loop, go to next iteration in for loop
			}
			// if room already exists, increment direction iterator and try again
			else dit++;

			// if iterator is at end, exit the loop with an error message
			if (dit == v_dirs.end()) {
				cout << "ERROR. MAP CREATION FAILURE." << endl;
				// start map wipe procedure
				return; // quit map creation
			}
		}
	}
}

// new room creation function for map gen
bool Map::room_create(Room*& current, int direction, Room* next) {
	int x = current->x;
	int y = current->y;
	// if check isn't out of bounds, and next room is empty, then create room!
	if (room_check(current, direction, next)) {
		if (next == nullptr) {
			// get room coords depending on search direction
			switch (direction) {
			case 0: // north
				x = x - 1;
				break;
			case 1: // east
				y = y + 1;
				break;
			case 2: // south
				x = x + 1;
				break;
			case 3: // west
				y = y - 1;
				break;
			}
			cout << "CREATING ROOM & MOVING TO: (" << x << ", " << y << ")" << endl;
			map[x][y] = new Room(x, y); // create new room at target location
			door_create(current, direction, map[x][y]); // create door between current room and new room
			current = map[x][y]; // move to new room
			// cout << "CURRENT ROOM DOOR COUNT: " << room->door_count << endl;
			return true;
		}
		else {
			cout << "ROOM ALREADY EXISTS." << endl;
			return false;
		}
	}
	else {
		cout << "CANNOT CREATE ROOM." << endl;
		return false;
	}
}

// door creation function (takes in x and y of new room, not the current one)
void Map::door_create(Room* current, int direction, Room* next) {
	int indir;
	switch (direction) {
	case 0:
		indir = 2;
		break;
	case 1:
		indir = 3;
		break;
	case 2:
		indir = 0;
		break;
	case 3:
		indir = 1;
		break;
	}
	// if the other room is the exit, create a Big Door
	if (next->is_exit) door = new BigDoor(current, next);
	// else create regular door
	else door = new Door(current, next);
	current->a_doors[direction] = door; // place outgoing door in current room
	current->door_count++;
	next->a_doors[indir] = door; // place incoming door in opposite area of other room
	next->door_count++;
	door = nullptr; // no dangling pointers
}

// returns true if checked space has a room in it!
bool Map::room_check(Room* current, int direction, Room*& next) {
	int x = current->x;
	int y = current->y;
	next = nullptr; // reset connection
	// check that search does not extend beyond map boundaries, then check for an exit in the given direction
	switch (direction) {
		case 0: // check north
			if (x - 1 < 0) {
				cout << "OUT OF BOUNDS." << endl;
				return false;
			}
			else if (map[x - 1][y]) { // north room exists
					next = map[x - 1][y]; // save room
			}
			return true; // return that area is not out of bounds?
		case 1: // check east
			if (y + 1 >= size) {
				cout << "OUT OF BOUNDS." << endl;
				return false;
			}
			else if (map[x][y + 1]) { // east
					next = map[x][y + 1];
			}
			return true;
		case 2: // check south
			if (x + 1 >= size) {
				cout << "OUT OF BOUNDS." << endl;
				return false;
			}
			else if (map[x + 1][y]) { // south
					next = map[x + 1][y];
			}
			return true;
		case 3: // check south
			if (y - 1 < 0) {
				cout << "OUT OF BOUNDS." << endl;
				return false;
			}
			else if (map[x][y - 1]) { // west
					next = map[x][y - 1];
			}
			return true;
	}
	// if it gets down here, something real bad happened
	// return false;
}

// DRAW MAP
// this version draws the map in its entirety
void Map::draw_full(Player& player) {
	cout << "\nDUNGEON MAP:\n";
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < 2; k++) { // iterate through same row twice; once for rooms/horizontal connections, once for vertical
			for (int j = 0; j < size; j++) {
				if (k == 0) { // first iteration
					if (map[i][j]) { // true if pointer not null (room exists)
						// draw "you are here" icon if player is in room
						if (map[i][j] == player.room) cout << "[X]";
						// else draw  default map icon for each room
						else cout << map[i][j]->map_icon;
					}
					else cout << " x "; // no room exists there

					// draw horizontal connections
					if (!map[i][j]) cout << " "; // if no room, empty space for alignment
					else if (map[i][j]->a_doors[1]) cout << "-"; // if east door exists, draw connection indicator (horizontal)
					else cout << " "; // separator
				}
				else { // second iteration (south/north connections)
					if (!map[i][j]) cout << "   "; // empty space for alignment
					else if (map[i][j]->a_doors[2]) cout << " | "; // if south door exists, connection indicator (vertical)
					else cout << "   "; // if room exists but no connection, empty space
					cout << " "; // separator
				}
			}
			cout << endl; // return for next row
		}
	}
	cout << "\nLEGEND:" << endl;
	cout << "[X] - You are here" << endl;
	cout << "[S] - Starting room" << endl;
	cout << "[E] - Exit" << endl;
}

/* // DRAW MAP 2
// this version only draws rooms the player has visited
void Map::draw_player(Player& player) {
	cout << "\nDUNGEON MAP:\n";
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < 2; k++) { // iterate through same row twice; once for rooms/horizontal connections, once for vertical
			for (int j = 0; j < size; j++) {
				if (k == 0) { // first iteration

					// draw CURRENT room
					if (map[i][j]) { // true if pointer not null (room exists)
						if (map[i][j]->visited) { // draw room only if player has visited!!
							// draw "you are here" icon if player is in room
							if (map[i][j] == player.room) cout << "[X]";
							// else draw  default map icon for each room
							else cout << map[i][j]->map_icon;
						}
					}
					else cout << " x "; // no room exists there

					// draw connections
					// check NEXT (right/below rooms) instead of current room for this version!
					// right: y + 1
					// below: x + 1

					/* // horizontal connections
					// check that not looking out of bounds
					if ((i + 1) < size) {
						// check if NEXT (right) room exists
						if (map[i + 1][j]) {
							// check if that room has been visited AND has a west door
							if ((map[i + 1][j]->visited) && (map[i + 1][j]->a_doors[3])) cout << " - "; // if so, draw connection
							else cout << "   "; // else draw blank space
						}
						/* if (!map[i + 1][j]) cout << " "; // if room does not exist, draw empty space for alignment
						// if next room exists AND has been visited AND west door in NEXT room exists, draw connection indicator to the right
						// of current room (horizontal)
						else if ((map[i + 1][j]->visited) && (map[i + 1][j]->a_doors[3])) cout << "-";
						else cout << " "; // separator for no connection 
					}
				}
				else { // second iteration (south/north connections)
					if (!map[i][j]) cout << "   "; // empty space for alignment
					 // if south door exists & room has been visited, connection indicator below (vertical)
					else if ((map[i][j]->visited) && (map[i][j]->a_doors[2])) cout << " | ";
					else cout << "   "; // if room exists but no connection, empty space
					cout << " "; // separator 
				}
			}
			cout << endl; // return for next row
		}
	}
	cout << "\nLEGEND:" << endl;
	cout << "[X] - You are here" << endl;
	cout << "[S] - Starting room" << endl;
	cout << "[E] - Exit" << endl;
} */
