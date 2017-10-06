#pragma once
#include "../entity.h"

enum ItemType {RH, BA, BD, PH, WA, WD, SMALL, MEDIUM, MERCHANT_HOARD, DRAGON_HOARD};

class Item : public Entity {
  ItemType itemType;
public:
  void setSubType(ItemType type);
  ItemType getSubType() const;
};
