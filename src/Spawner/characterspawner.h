#pragma once
#include "../Entities/Characters/character.h"
#include <memory>

class CharacterSpawner {
public:
	// Factory Method
	static std::shared_ptr<Character> createEntity(CharacterType type);
	// Spawns enemy
	std::shared_ptr<Entity> spawn(CharacterType type, std::pair<int, int> pos);
};
