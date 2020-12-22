#include "BigKey.h"

using namespace std;

BigKey::BigKey(void) { // constructor
	this->name = "Big Key";
	this->desc = "A very large, ornate golden key. Must be important.";
	this->multiuse = false;
	this->takeable = true;
	this->equippable = false;
}
