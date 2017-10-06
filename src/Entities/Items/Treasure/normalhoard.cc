#include "normalhoard.h"

// Create new Treasure, set to Small by default
NormalHoard::NormalHoard() {
	avatar = 'G';
	setType(TREASURE);
	setSubType(ItemType::SMALL);
}

// Create new Treasure, set to Small by default
NormalHoard::NormalHoard(ItemType type) {
	avatar = 'G';
	setType(TREASURE);
	setSubType(type);
}
