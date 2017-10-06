#include "entity.h"
using namespace std;

// default ctor sets pos to (-1, -1) and type to Player
Entity::Entity() : type{ PLAYER }, pos{ make_pair<int,int>(-1, -1) } {}

Entity::Entity(EntityType type, pair<int, int> pos) : type{ type }, pos{ pos } {}

// set type of entity (from EntityType)
void Entity::setType(EntityType type) { this->type = type; }

EntityType Entity::getType() const { return type; }

void Entity::setPosition(int x, int y) { pos = make_pair(x, y); }

char Entity::getAvatar(){ return avatar; }

void Entity::setPosition(pair<int, int> pos) { this->pos = pos; }

pair<int, int> Entity::getPosition() const { return pos; }

Entity::~Entity() {}

std::ostream& operator<<(std::ostream &out, const Entity &e) {
	out << e.avatar;
	return out;
}
