#include "player.h"
#include <memory>
#pragma once

class Vampire : public Player{
public:
    Vampire();
    std::string attack(std::shared_ptr<Character> c) override;
    std::string usePot(std::shared_ptr<Potion> pot) override;
};
