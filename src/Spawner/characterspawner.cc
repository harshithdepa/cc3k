#include "characterspawner.h"
#include "../Entities/Characters/Players/goblin.h"
#include "../Entities/Characters/Players/drow.h"
#include "../Entities/Characters/Players/vampire.h"
#include "../Entities/Characters/Players/shade.h"
#include "../Entities/Characters/Players/troll.h"
#include "../Entities/Characters/Enemies/dragon.h"
#include "../Entities/Characters/Enemies/dwarf.h"
#include "../Entities/Characters/Enemies/elf.h"
#include "../Entities/Characters/Enemies/halfling.h"
#include "../Entities/Characters/Enemies/human.h"
#include "../Entities/Characters/Enemies/merchant.h"
#include "../Entities/Characters/Enemies/orc.h"
using namespace std;

shared_ptr<Character> CharacterSpawner::createEntity(CharacterType type) {
	shared_ptr<Character> e;

	if (type == GOBLIN) e = make_shared<Goblin>();
	else if (type == DROW) e = make_shared<Drow>();
	else if (type == VAMPIRE) e = make_shared<Vampire>();
	else if (type == SHADE) e = make_shared<Shade>();
	else if (type == TROLL) e = make_shared<Troll>();
	else if (type == DWARF) e = make_shared<Dwarf>();
	else if (type == ELF) e = make_shared<Elf>();
	else if (type == ORC) e = make_shared<Orc>();
	else if (type == MERCHANT) e = make_shared<Merchant>();
	else if (type == HUMAN) e = make_shared<Human>();
	else if (type == DRAGON) e = make_shared<Dragon>();
	else if (type == HALFLING) e = make_shared<Halfling>();

	e->setSubType(type);

	return e;
}

shared_ptr<Entity> CharacterSpawner::spawn(CharacterType type, std::pair<int, int> pos) {
	shared_ptr<Entity> s = createEntity(type);
	s->setPosition(pos);
	return s;
}
