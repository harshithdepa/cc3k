#include "tile.h"
using namespace std;

Tile::Tile() : chamber { 0 }, type{ VOID } {};

// initialize entity
void Tile::setEntity(shared_ptr<Entity> ent) {
  e = ent;
  type = ENT;
};

// Remove entity from Tile
void Tile::removeEntity(){
  e = nullptr;
  type = FLOOR;
}

// sets type of tile
void Tile::setType(Tile::Type type) { this->type = type; }

// sets chamber number
void Tile::setChamber(int num) { chamber = num; }

// get pointer to entity
shared_ptr<Entity> Tile::getEntityPtr() const { return e; }

// get type of tile
Tile::Type Tile::getType() const { return type; }

// get chamber number
int Tile::getChamber() const { return chamber; }

// converts type to appropriate char for display
char tileToChar(const Tile t) {
	Tile::Type type = t.getType();
	if (type == Tile::VWALL) return '|';
	if (type == Tile::HWALL) return '-';
	if (type == Tile::DOORWAY) return '+';
	if (type == Tile::PASSAGE) return '#';
	if (type == Tile::FLOOR) return '.';
	/*{
		shared_ptr<Entity> e = t.getEntityPtr();
		if (e.get() == nullptr) return '.';  // normal floor tile
		else return e->getAvatar();  // entity on floor tile
	}*/
	// Void tile
	return ' ';
}

// display tile on screen
std::ostream& operator<<(std::ostream &out, const Tile &t) {
	out << tileToChar(t);
	return out;
}
