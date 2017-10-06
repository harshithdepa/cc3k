#pragma once
#include <memory>
#include "../../Characters/Enemies/dragon.h"
#include "../treasure.h"

class Dragon;

class DragonHoard : public Treasure {
  std::shared_ptr<Dragon> dptr;
public:
  DragonHoard();
	void setDragon(std::shared_ptr<Dragon> newptr);
	void removeDragon();
	std::shared_ptr<Dragon> getDragon() const;
  bool hasDragon() const;
};
