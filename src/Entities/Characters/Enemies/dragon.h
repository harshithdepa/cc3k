#pragma once
#include <memory>
#include "enemy.h"

class DragonHoard;

class Dragon : public Enemy {
	std::shared_ptr<DragonHoard> dhptr;
public:
  Dragon();
	void setHoard(std::shared_ptr<DragonHoard> newptr);
	std::shared_ptr<DragonHoard> getHoard() const;
	bool hasHoard() const;
	~Dragon();
};
