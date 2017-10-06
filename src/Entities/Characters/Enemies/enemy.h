#pragma once
#include "../character.h"
#include <memory>

class Enemy : public Character {
public:
	std::string attack(std::shared_ptr<Character> c) override;
	bool operator<(const Enemy &e2);
};

bool operator<(const Enemy &e1, const Enemy &e2);
