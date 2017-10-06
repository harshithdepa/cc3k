#include "../entity.h"
#include "../../directions.h"
#include <memory>
#pragma once

enum CharacterType { SHADE, DROW, VAMPIRE, TROLL, GOBLIN, DRAGON, DWARF, ELF, HALFLING, HUMAN, MERCHANT, ORC };

class Character : public Entity {
protected:
  int Atk;
  int Def;
	int Hp;
	int maxHp;
	int Gold;
	CharacterType Race;
public:
	int getHp();
  int getmaxHp();
  void setHp(int hp);
	int getAtk();
	int getDef();
	int getGold();
  void addGold(int gold);
  virtual int getatkMod();
  virtual int getdefMod();
	bool isDead();
	virtual void move(std::pair<int, int> pos);
	void setSubType(CharacterType type);
	CharacterType getSubType() const;
	virtual std::string attack(std::shared_ptr<Character> c) = 0;
};
