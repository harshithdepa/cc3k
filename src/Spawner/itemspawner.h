#pragma once
#include "../Entities/Items/item.h"
#include <memory>

class ItemSpawner {
public:
	// Factory Method
	static std::shared_ptr<Item> createEntity(ItemType type);
	// Spawns enemy
	std::shared_ptr<Entity> spawn(ItemType type, std::pair<int, int> pos);
};
