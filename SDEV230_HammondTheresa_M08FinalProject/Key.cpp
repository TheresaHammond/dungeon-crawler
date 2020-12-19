// Keys are spawned as items that the player can pick up,
// but are not useable from the player's inventory; must
// interact with an item that requires a key. This is why we
// delete the actual key object when the player picks them up.
// This means that players cannot DROP keys.

// Keys are stored as a number/flag in the player's inventory.

#include "Key.h"

using namespace std;

Key::Key(void) { // constructor
	this->name = "Key";
	this->desc = "It's a plain, rusty metal key.";
	this->multiuse = false;
	this->takeable = true;
	this->equippable = false;
}
