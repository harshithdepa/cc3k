#include "human.h"

Human::Human(){
    Hp = 140;
    avatar = 'H';
    Atk = 20;
    Def = 20;
    Gold = 4;
    type = EntityType::ENEMY;
    Race = CharacterType::HUMAN;
}
