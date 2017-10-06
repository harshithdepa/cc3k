#include "drow.h"
#include "../character.h"
#include <algorithm>
#include <cstdlib>

Drow::Drow() {
    avatar = '@';
    Hp = 150;
    Atk = 25;
    Def = 15;
    Gold = 0;
    type = EntityType::PLAYER;
    Race = CharacterType::DROW;
    maxHp = 150;
}

std::string Drow::usePot(std::shared_ptr<Potion> pot){
    switch (pot->getSubType())
    {
    case ItemType::RH:
        setHp(std::max(getHp() + 15, getmaxHp()));
        return "RH";
    case ItemType::BA:
        setatkMod(getatkMod() + 7);
        return "BA";
    case ItemType::BD:
        setdefMod(getdefMod() + 7);
        return "BD";
    case ItemType::PH:
        setHp(std::max(getHp() - 15, 0));
        return "PH";
    case ItemType::WA:
        setatkMod(getatkMod() - 7);
        return "WA";
    case ItemType::WD:
        setdefMod(getdefMod() - 7);
        return "WD";
		default:
			return "INVALID POTION";
    }
}
