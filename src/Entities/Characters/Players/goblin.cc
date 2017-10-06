#include "goblin.h"
#include <algorithm>

Goblin::Goblin(){
    avatar = '@';
    Hp = 110;
    maxHp = 110;
    Atk = 15;
    Def = 20;
    Gold = 0;
    type = EntityType::PLAYER;
    Race = CharacterType::GOBLIN;
}

std::string Goblin::attack(std::shared_ptr<Character> c){
    bool hit = true;
    int dmg = 0;
    if(c->getSubType() == CharacterType::HALFLING && ((rand() % 2)+1 == 2)){
        hit = false;
    }
    if(hit){
        int atk = std::max(getAtk() + getatkMod(), 0);
        int enemydef = c->getDef();
        dmg = (atk*100 + 100 + enemydef - 1)/ (100 + enemydef);
        c->setHp(std::max(c->getHp() - dmg, 0));
        if(c->isDead()){
            addGold(c->getGold()+5);
        }
    }
		return std::string(1, c->getAvatar()) + " " + std::to_string(dmg);
}
