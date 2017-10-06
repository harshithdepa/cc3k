#include "player.h"
#include <memory>
#pragma once

class Troll : public Player{
public:
    Troll();
    std::string attack(std::shared_ptr<Character> c) override;
    void move(std::pair<int, int> pos) override;
    std::string usePot(std::shared_ptr<Potion> pot) override;
};
