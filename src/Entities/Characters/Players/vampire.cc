#include "vampire.h"
#include <algorithm>

Vampire::Vampire(){
    avatar = '@';
    Hp = 50;
    Atk = 25;
    Def = 25;
    Gold = 0;
    type = EntityType::PLAYER;
    Race = CharacterType::VAMPIRE;
}

std::string Vampire::attack(std::shared_ptr<Character> c){
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
            addGold(c->getGold());
        }
        if(c->getSubType() == CharacterType::DWARF){
            setHp(std::max(getHp() - 5, 0));
        } else {
            setHp(getHp() + 5);
        }
    }
		return std::string(1, c->getAvatar()) + " " + std::to_string(dmg);
}

std::string Vampire::usePot(std::shared_ptr<Potion> pot){
    switch (pot->getSubType())
    {
    case ItemType::RH:
        setHp(getHp() + 10);
        return "RH";
    case ItemType::BA:
        setatkMod(getatkMod() + 5);
        return "BA";
    case ItemType::BD:
        setdefMod(getdefMod() + 5);
        return "BD";
    case ItemType::PH:
        setHp(std::max(getHp() - 10, 0));
        return "PH";
    case ItemType::WA:
        setatkMod(getatkMod() - 5);
        return "WA";
    case ItemType::WD:
        setdefMod(getdefMod() - 5);
        return "WD";
		default:
			return "INVALID POTION";
    }
}
