#include "itemspawner.h"
#include "../Entities/Items/potion.h"
#include "../Entities/Items/Treasure/normalhoard.h"
#include "../Entities/Items/Treasure/dragonhoard.h"
using namespace std;

shared_ptr<Item> ItemSpawner::createEntity(ItemType type) {
	shared_ptr<Item> e;
	int typeIndex = static_cast<int>(type);

	// Dragon Hoard
	if (type == DRAGON_HOARD) e = make_shared<DragonHoard>();
	// Treasure (other than dragon hoard)
	else if (typeIndex >= 6) e = make_shared<NormalHoard>();
	// Potions
	else e = make_shared<Potion>();

	// set item type
	e->setSubType(type);

	return e;
}

shared_ptr<Entity> ItemSpawner::spawn(ItemType type, std::pair<int, int> pos) {
	shared_ptr<Entity> s = createEntity(type);
	s->setPosition(pos);
	return s;
}
