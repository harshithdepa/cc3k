#include "enemy.h"
#include <memory>
#pragma once

class Elf : public Enemy{
public:
    Elf();
    std::string attack(std::shared_ptr<Character> c) override;
};
