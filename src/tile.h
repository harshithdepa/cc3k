#pragma once
#include <memory>
#include "Entities/entity.h"
#include <ostream>

class Tile {
public:
  Tile ();
  // types of tiles
  enum Type { VWALL, HWALL, DOORWAY, PASSAGE, FLOOR, VOID, ENT };
  void setEntity(std::shared_ptr<Entity> ent);
  void removeEntity();
  void setType(Type type);
  void setChamber(int num);
  std::shared_ptr<Entity> getEntityPtr() const;
  Type getType() const;
  int getChamber() const;
	friend std::ostream& operator<<(std::ostream &out, const Tile &t);
private:
  std::shared_ptr<Entity> e;
  int chamber; // starts from 1
  Tile::Type type;
};
