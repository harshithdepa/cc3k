#include "item.h"

void Item::setSubType(ItemType type) { itemType = type; }

ItemType Item::getSubType() const { return itemType; }