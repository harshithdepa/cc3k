#include "character.h"

int Character::getHp(){ return Hp; }

int Character::getmaxHp(){ return maxHp; }

void Character::setHp(int hp){ Hp = hp; }

int Character::getAtk(){ return Atk; }

int Character::getDef(){ return Def; }

int Character::getGold(){ return Gold; }

void Character::addGold(int gold) { Gold += gold; }

void Character::move(std::pair<int, int> pos){ setPosition(pos); }

bool Character::isDead(){ return (Hp == 0); }

void Character::setSubType(CharacterType type) { Race = type; }

int Character::getatkMod(){
    return 0;
}
int Character::getdefMod(){
    return 0;
}

CharacterType Character::getSubType() const { return Race; }
