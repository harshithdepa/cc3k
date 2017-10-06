#include "elf.h"
#include <algorithm>

Elf::Elf(){
    Hp = 140;
    avatar = 'E';
    Atk = 30;
    Def = 10;
    Gold = (rand() % 2)+1;
    type = EntityType::ENEMY;
    Race = CharacterType::ELF;
}

std::string Elf::attack(std::shared_ptr<Character> c){
    bool hit = true;
    if((rand() % 2)+1 == 2){
        hit = false;
    }
    int dmg = 0;
    if(hit){
        int atk = getAtk();
				int playerDef = std::max(c->getDef() + c->getdefMod(), 0);
				dmg += (atk * 100 + 100 + playerDef - 1) / (100 + playerDef);
        c->setHp(std::max(c->getHp() - dmg, 0));
    }
    if(c->getSubType() != CharacterType::DROW){
        hit = true;
        if((rand() % 2)+1 == 2){
            hit = false;
        }
        if(hit){
            int atk = getAtk();
						int playerDef = std::max(c->getDef() + c->getdefMod(), 0);
						dmg += (atk * 100 + 100 + playerDef - 1) / (100 + playerDef);
            c->setHp(std::max(c->getHp() - dmg, 0));
        }
    }
    return std::string(1, getAvatar()) + " " + std::to_string(dmg);
}
