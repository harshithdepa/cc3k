#pragma once
#include "../treasure.h"

class NormalHoard : public Treasure {
public:
  NormalHoard();
  NormalHoard(ItemType type);
};
