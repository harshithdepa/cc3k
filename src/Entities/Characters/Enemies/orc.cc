#include "orc.h"
#include <algorithm>

Orc::Orc(){
    Hp = 180;
    avatar = 'O';
    Atk = 30;
    Def = 25;
    Gold = (rand() % 2)+1;
    type = EntityType::ENEMY;
    Race = CharacterType::ORC;
}

std::string Orc::attack(std::shared_ptr<Character> c){
    bool hit = true;
    int dmg = 0;
    if((rand() % 2)+1 == 2){
        hit = false;
    }
    if(hit){
        int atk = getAtk();
        int enemydef = std::max(c->getDef() + c->getatkMod(), 0);
        if(c->getSubType() != CharacterType::GOBLIN){
            dmg = ((atk*100 + 100 + enemydef - 1)/ (100 + enemydef)) *3 / 2;
            c->setHp(std::max(c->getHp() - dmg, 0));
        } else {
            dmg = (atk*100 + 100 + enemydef - 1)/ (100 + enemydef);
            c->setHp(std::max(c->getHp() - dmg, 0));
        }
    }
		return std::string(1, getAvatar()) + " " + std::to_string(dmg);
}
