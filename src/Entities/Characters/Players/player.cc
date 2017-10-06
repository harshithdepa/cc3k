#include "player.h"
#include <algorithm>

int Player::getatkMod(){
    return atkMod;
}

void Player::setatkMod(int mod){
    atkMod = mod;
}

void Player::setdefMod(int mod){
    defMod = mod;
}

int Player::getdefMod(){
    return defMod;
}

bool Player::hasAttackedMerch() const { return attackedMerch; }

void Player::attackMerch(){ attackedMerch = true; }

void Player::resetMod(){
    atkMod = 0;
    defMod = 0;
}

std::string Player::attack(std::shared_ptr<Character> c){
    bool hit = true;
    int dmg = 0;
    if(c->getSubType() == CharacterType::HALFLING && ((rand() % 2)+1 == 2)){
        hit = false;
    }
    if(hit){
        int atk = std::max(getAtk() + getatkMod(), 0);
        int enemydef = c->getDef();
				dmg = (atk * 100 + 100 + enemydef - 1) / (100 + enemydef);
        c->setHp(std::max(c->getHp() - dmg, 0));
        if(c->isDead()){
            addGold(c->getGold());
        }
    }
    return std::string(1, c->getAvatar()) + " " + std::to_string(dmg);
}

std::string Player::usePot(std::shared_ptr<Potion> pot){
    switch (pot->getSubType())
    {
    case ItemType::RH:
        setHp(std::max(getHp() + 10, getmaxHp()));
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
