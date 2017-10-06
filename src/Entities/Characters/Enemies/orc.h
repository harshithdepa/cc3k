#include "enemy.h"
#include <memory>
#pragma once

class Orc : public Enemy{
public:
    Orc();
    std::string attack(std::shared_ptr<Character> c) override;
};
