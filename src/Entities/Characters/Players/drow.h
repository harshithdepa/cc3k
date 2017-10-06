#include "player.h"
#pragma once
#include <memory>

class Drow : public Player{
public:
    Drow();
    std::string usePot(std::shared_ptr<Potion> pot) override;
};
