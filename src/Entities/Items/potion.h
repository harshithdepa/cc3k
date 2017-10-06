#pragma once
#include "item.h"

class Potion : public Item {
  bool hasBeenSeen;
public:
  Potion();
  Potion(ItemType type);
  bool wasSeen();
};
