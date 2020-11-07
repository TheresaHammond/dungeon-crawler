#include "Map.h"

Map::Map(void) { // CONSTRUCTOR (this will do map generation later!)
	this->size = 3;
	this->entrance_x = 0;
	this->entrance_y = 0;
	this->exit_x = size;
	this->exit_y = size;
}
void Map::map_generate() {
	// map gen code
}
