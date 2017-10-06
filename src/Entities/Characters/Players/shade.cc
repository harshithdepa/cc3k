#include "shade.h"

Shade::Shade(){
    avatar = '@';
    Hp = 125;
    maxHp = 125;
    Atk = 25;
    Def = 25;
    Gold = 0;
    type = EntityType::PLAYER;
    Race = CharacterType::SHADE;
}
