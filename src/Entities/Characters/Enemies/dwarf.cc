#include "dwarf.h"

Dwarf::Dwarf(){
    Hp = 100;
    avatar = 'W';
    Atk = 20;
    Def = 30;
    Gold = (rand() % 2)+1;
    type = EntityType::ENEMY;
    Race = CharacterType::DWARF;
}
