#include "dragonhoard.h"
using namespace std;

// Create new DragonHoard
DragonHoard::DragonHoard() {
	avatar = 'G';
	setType(TREASURE);
	setSubType(ItemType::DRAGON_HOARD);
}

bool DragonHoard::hasDragon() const { return (dptr != nullptr); }

void DragonHoard::setDragon(shared_ptr<Dragon> newptr){ dptr = newptr; }

void DragonHoard::removeDragon() { dptr.reset(); }

shared_ptr<Dragon> DragonHoard::getDragon() const{ return dptr; }
