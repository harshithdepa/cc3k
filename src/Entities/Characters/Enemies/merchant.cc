#include "merchant.h"

Merchant::Merchant(){
    Hp = 30;
    avatar = 'M';
    Atk = 70;
    Def = 5;
    Gold = 4;
    type = EntityType::ENEMY;
    Race = CharacterType::MERCHANT;
}
