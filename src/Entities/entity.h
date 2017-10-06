#pragma once
#include <utility>
#include <string>
#include <ostream>

enum EntityType { PLAYER, ENEMY, BOSS, POTION, TREASURE, STAIRS };

class Entity {
public:
	Entity();
	Entity(EntityType type, std::pair<int, int> pos);
	void setType(EntityType type);
  EntityType getType() const;
  char getAvatar();
	void setPosition(int x, int y);
	void setPosition(std::pair<int, int> pos);
  std::pair<int, int> getPosition() const;
	friend std::ostream& operator<<(std::ostream &out, const Entity &e);
	virtual ~Entity();
protected:
	char avatar;
	EntityType type;
private:
  std::pair<int, int> pos;

};
