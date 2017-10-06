#pragma once
#include "../character.h"
#include "../../Items/potion.h"
#include <memory>

class Player : public Character {
protected:
	int atkMod;
	int defMod;
	bool attackedMerch = false;
public:
	int getatkMod() override;
	void setatkMod(int mod);
	int getdefMod() override;
	void setdefMod(int mod);
	bool hasAttackedMerch() const;
	void attackMerch();
	void resetMod();
	std::string attack(std::shared_ptr<Character> c) override;
	virtual std::string usePot(std::shared_ptr<Potion> pot);
};
