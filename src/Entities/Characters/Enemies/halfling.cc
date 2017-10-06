#include "halfling.h"

Halfling::Halfling(){
    Hp = 100;
    avatar = 'L';
    Atk = 15;
    Def = 20;
    Gold = (rand() % 2)+1;
    type = EntityType::ENEMY;
    Race = CharacterType::HALFLING;
}
