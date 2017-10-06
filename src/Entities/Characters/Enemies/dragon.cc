#include "dragon.h"
#include "../../Items/Treasure/dragonhoard.h"
using namespace std;

Dragon::Dragon() {
    Hp = 150;
    avatar = 'D';
    Atk = 20;
    Def = 20;
    Gold = 0;
    type = EntityType::ENEMY;
    Race = CharacterType::DRAGON;
}

bool Dragon::hasHoard() const { return !(!dhptr); }

void Dragon::setHoard(shared_ptr<DragonHoard> newptr) { dhptr = newptr; }

shared_ptr<DragonHoard> Dragon::getHoard() const { return dhptr; }

Dragon::~Dragon() {
  dhptr->removeDragon();
  dhptr.reset();
}
