#include "player.h"
#include <memory>
#pragma once

class Goblin : public Player{
public:
    Goblin();
    std::string attack(std::shared_ptr<Character> c) override;
};
