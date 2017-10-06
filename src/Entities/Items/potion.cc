#include "potion.h"
using namespace std;

// Create new Potion, set to Restore Health by default
Potion::Potion(){
	hasBeenSeen = false;
	avatar = 'P';
	setType(POTION);
	setSubType(ItemType::RH);
}

// Creates a Potion with a specific Item::Type
Potion::Potion(ItemType type){
	hasBeenSeen = false;
	avatar = 'P';
	setType(POTION);
	setSubType(type);
}

bool Potion::wasSeen(){
	if(!hasBeenSeen){
		hasBeenSeen = true;
		return false;
	}
	return hasBeenSeen;
}
