#pragma once
#include "../Entities/stairs.h"
#include <memory>

class StairsSpawner {
public:
	// Factory Method
	static std::shared_ptr<Stairs> createEntity();
	// Spawns enemy
	std::shared_ptr<Entity> spawn(std::pair<int, int> pos);
};
