#include "stairsspawner.h"
using namespace std;

shared_ptr<Stairs> StairsSpawner::createEntity() {
	shared_ptr<Stairs> e = make_shared<Stairs>();
	return e;
}

shared_ptr<Entity> StairsSpawner::spawn(std::pair<int, int> pos) {
  shared_ptr<Entity> s = createEntity();
	s->setPosition(pos);
  return s;
}
