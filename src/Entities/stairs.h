#pragma once
#include "entity.h"

class Stairs : public Entity {
public:
	Stairs() { 
		avatar = '\\'; 
		type = EntityType::STAIRS;
	};
};
