#include "enemy.h"
#include <algorithm>

std::string Enemy::attack(std::shared_ptr<Character> c){
    bool hit = true;
    int dmg = 0;
    if((rand() % 2)+1 == 2){
        hit = false;
    }
    if(hit){
        int atk = getAtk();
        int playerDef = std::max(c->getDef() + c->getdefMod(), 0);
        dmg = (atk*100 + 100 + playerDef - 1)/ (100 + playerDef);
        c->setHp(std::max(c->getHp() - dmg, 0));
    }
    return std::string(1, getAvatar()) + " " + std::to_string(dmg);
}

bool operator<(const Enemy &e1, const Enemy &e2){
    std::pair<int, int> pos1 = e1.getPosition();
    std::pair<int, int> pos2 = e2.getPosition();
    if(pos1.first < pos2.first || (pos1.first == pos2.first && pos1.second < pos2.second)){
        return true;
    } else {
        return false;
    }
}

bool Enemy::operator<(const Enemy &e2){
    std::pair<int, int> pos1 = getPosition();
    std::pair<int, int> pos2 = e2.getPosition();
    if(pos1.first < pos2.first || (pos1.first == pos2.first && pos1.second < pos2.second)){
        return true;
    } else {
        return false;
    }
}
