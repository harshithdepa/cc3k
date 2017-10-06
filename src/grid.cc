#include <cstdlib>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "grid.h"
#include "tile.h"
#include "Entities/Characters/character.h"
#include "Entities/Characters/Enemies/enemy.h"
#include "Entities/Characters/Enemies/dragon.h"
#include "Entities/Characters/Enemies/orc.h"
#include "Entities/Characters/Enemies/elf.h"
#include "Entities/Items/item.h"
#include "Entities/Items/treasure.h"
#include "Entities/Items/Treasure/normalhoard.h"
#include "Entities/Items/Treasure/dragonhoard.h"
#include "Spawner/characterspawner.h"
#include "Spawner/itemspawner.h"
#include "Spawner/stairsspawner.h"
using namespace std;

// converts char from file to appropriate type
Tile::Type charToTile(char c) {
  switch(c) {
  case '|': return Tile::VWALL;
  case '-': return Tile::HWALL;
  case '+': return Tile::DOORWAY;
  case '#': return Tile::PASSAGE;
  case '.': return Tile::FLOOR;
  case ' ': return Tile::VOID;  // should not happen
    default:  cout << "ERROR: Invalid character in map!";
              exit(1);
  }
}

// converts char to appropriate entity
shared_ptr<Entity> Grid::charToEntity(char ch, int r, int c) {
	shared_ptr<Entity> eptr;
	pair<int, int> pos = make_pair(r, c);

	switch (ch) {
	// Spawn Items
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
		ItemSpawner is;
		eptr = is.spawn(static_cast<ItemType>(ch - '0'), pos);  // create items from ItemType
		break;
	}
	// Spawn Player
	case '@': {
		player->setPosition(pos);
		return player;
	}
	// Spawn Enemy
	case 'H': case 'W': case 'E': case 'O': case 'L': case 'M': case 'D': {
		CharacterSpawner cs;
		if (ch == 'H') eptr = cs.spawn(HUMAN, pos);
		else if (ch == 'W') eptr = cs.spawn(DWARF, pos);
		else if (ch == 'E') eptr = cs.spawn(ELF, pos);
		else if (ch == 'O') eptr = cs.spawn(ORC, pos);
		else if (ch == 'L') eptr = cs.spawn(HALFLING, pos);
		else if (ch == 'M') eptr = cs.spawn(MERCHANT, pos);
		else eptr = cs.spawn(DRAGON, pos);
		break;
	}
	case '\\': {
		StairsSpawner ss;
		eptr = ss.spawn(pos);
		break;
	}
	}
	return eptr;
}

// returns true if positions are adjacent
bool isAdjacent(pair<int, int> pos1, pair<int, int> pos2) {
	return (abs(pos1.first - pos2.first) <= 1 && abs(pos1.second - pos2.second) <= 1);
}

// returns all neighbouring locations that are empty
vector<pair<int, int>> Grid::getEmptyNeighbours(pair<int, int> pos) {
  vector<pair<int, int>> emptyNeighbours;
  for(int y = pos.first-1; y <= pos.first+1; y++){
    for(int x = pos.second-1; x <= pos.second+1; x++){
      if((x != pos.second || y != pos.first) && x >= 0 && y >= 0 && x < WIDTH && y < BOARDHEIGHT){
         if(theGrid[y][x].getType() == Tile::FLOOR){
           emptyNeighbours.push_back(make_pair(y, x));
         }
      }
    }
  }
  return emptyNeighbours;
}

// returns location of random empty neighbouring Tile
pair<int, int> Grid::findEmptyNeighbour(pair<int, int> pos) {
  vector<pair<int, int>> pairs;
  for(int y = pos.first-1; y <= pos.first+1; y++){
    for(int x = pos.second-1; x <= pos.second+1; x++){
      if((x != pos.second || y != pos.first) && x >= 0 && y >= 0 && x < WIDTH && y < BOARDHEIGHT){
         if(theGrid[y][x].getType() == Tile::FLOOR){
           pairs.push_back(make_pair(y, x));
         }
      }
    }
  }
  if(pairs.size() > 0) return pairs[rand()% pairs.size()];
  return make_pair(-1, -1);
}

// returns true if position has any empty neighbouring Tiles
bool Grid::hasEmptyNeighbour(pair<int, int> pos) {
  return findEmptyNeighbour(pos) != make_pair(-1,-1);
}

// returns postion of empty tile inside specified (chamber number - 1)
// if dragonHoard, tile must have at least one empty tile beside it
pair<int, int> Grid::getEmptyTile(int chamberNum, bool dragonHoard) {
  int size = chambers[chamberNum].size();
  int rng = rand() % size;

	pair<int, int> pos;
  do {
    rng = rand() % size;
    pos = chambers[chamberNum][rng];

		if (theGrid[pos.first][pos.second].getType() == Tile::FLOOR) {
			if (!dragonHoard) break;
			if (hasEmptyNeighbour(pos)) break;
		}
	} while (true);
  return pos;
}

// assgns chamber number to floor tiles in chamber and returns column of end of chamber
int Grid::assignChamber(int n, int r, int c) {
  theGrid[r][c].setChamber(n);
  chambers[n-1].push_back(make_pair(r, c));
  // recursively assign chamber number to rest of floors
  if (r > 3 && theGrid[r - 1][c].getType() == Tile::FLOOR && !theGrid[r - 1][c].getChamber())
    assignChamber(n, r - 1, c);
  if (r < BOARDHEIGHT - 3 && theGrid[r + 1][c].getType() == Tile::FLOOR && !theGrid[r + 1][c].getChamber())
    assignChamber(n, r + 1, c);
  if (c > 3 && theGrid[r][c - 1].getType() == Tile::FLOOR && !theGrid[r][c - 1].getChamber())
      assignChamber(n, r, c - 1);
  if (c < WIDTH - 3 && theGrid[r][c + 1].getType() == Tile::FLOOR && !theGrid[r][c + 1].getChamber())
      return assignChamber(n, r, c + 1);
  else return c + 1;  // returns next column if end of row or next tile is not a Floor tile
}

// retrieves next start of chamber starting from row r and column c and scanning from top-left to bottom-right.
// Returns (-1, -1) if no more free chambers
pair<int, int> Grid::getChamberStart(int r, int c) {
  do {
    // if end of row
    if (c >= WIDTH - 2) {
      r++;
      c = 2;
    } else c++;

    // check if end of grid
    if (r >= BOARDHEIGHT - 2) break;

    if (theGrid[r][c].getType() == Tile::FLOOR && !theGrid[r][c].getChamber()) return make_pair(r, c);
  } while (true);

  return make_pair(-1, -1);
}

// parse map from string
void Grid::stringToRow(string line, int r) {
  if (line.length() != (unsigned) WIDTH) {
    cout << "ERROR: improper map (incorrect width)";
    exit(1);
  }

	for (unsigned int c = 0; c < line.length(); c++) {
		char ch = line[c];
    Tile tile;
    // set type if not a blank char (Type Void is default)
    if (ch != ' ') {
			shared_ptr<Entity> e = charToEntity(ch, r, c);
			// is an entity
      if(e != nullptr) {
        tile.setType(Tile::FLOOR);
        tile.setEntity(e);
				switch (e->getType()) {
				case EntityType::ENEMY: enemies.push_back(dynamic_pointer_cast<Enemy>(e)); break;
				case EntityType::POTION: potions.push_back(dynamic_pointer_cast<Potion>(e)); break;
				case EntityType::TREASURE: treasures.push_back(dynamic_pointer_cast<Treasure>(e)); break;
				default: break;
				}
      } else { // not an entity
        tile.setType(charToTile(ch));
      }
    }
    theGrid[r].push_back(tile);
  }
}

// frees the grid
void Grid::clearGrid() {
	for (auto &row : theGrid) { row.clear(); }
	enemies.clear();
	potions.clear();
	treasures.clear();
    chambers.clear();
	actions.clear();
}

/* BIG 5 */

Grid::Grid() : floor{ 0 }, enemiesMove{ true }, theGrid { vector<vector<Tile>>(BOARDHEIGHT) } {}

Grid::~Grid() { clearGrid(); }

/* COMMANDS */

// toggles movement of enemies
void Grid::toggleEnemyMove() { enemiesMove = !enemiesMove; }

// returns the position of player if they move in direction dir
pair<int, int> Grid::getPos(Direction dir){
    pair<int, int> pos = player->getPosition();
    switch (dir){
    case Direction::NO :
        pos.first -= 1;
        break;
    case Direction::NE :
        pos.second += 1;
        pos.first -= 1;
        break;
    case Direction::EA :
        pos.second += 1;
        break;
    case Direction::SE :
        pos.second += 1;
        pos.first += 1;
        break;
    case Direction::SO :
        pos.first += 1;
        break;
    case Direction::SW :
        pos.second -= 1;
        pos.first += 1;
        break;
    case Direction::WE :
        pos.second -= 1;
        break;
    case Direction::NW :
        pos.second -= 1;
        pos.first -= 1;
        break;
    }
    return pos;
}

// use potion in specified direction
string Grid::usePotion(Direction dir) {
	pair<int, int> pos = getPos(dir);
	for (auto it = potions.begin(); it != potions.end(); it++) {
		if ((*it)->getPosition() == pos) {
			ItemType potType = (*it)->getSubType();
			player->usePot(*it);
			theGrid[pos.first][pos.second].removeEntity();
			potions.erase(it);
			switch (potType) {
			case ItemType::RH: return "RH";
			case ItemType::BA: return "BA";
			case ItemType::BD: return "BD";
			case ItemType::PH: return "PH";
			case ItemType::WA: return "WA";
			case ItemType::WD: return "WD";
			}
		}
	}
	cout << "ERROR: Invalid target. There is no potion there.\nEnter command: ";
	return "";
}

// attack enemy in specified direction
bool Grid::attack(Direction dir) {
	vector<shared_ptr<Enemy>>::iterator deletedIt = enemies.end();
	pair<int, int> pos = getPos(dir);
    for (vector<shared_ptr<Enemy>>::iterator it = enemies.begin(); it != enemies.end(); it++) {
    if((*it)->getPosition() == pos){
		int initGold = player->getGold();
        string enemyAtk = player->attack(*it);
		int goldDiff = player->getGold() - initGold;
		if (player->getSubType() == GOBLIN) goldDiff -= 5;
      if(enemyAtk == ""){
    		continue;
    	} else {
    		string action;
    		string enemyType = string(1, enemyAtk[0]);

        int hp = (*it)->getHp();
    		int dmg;
    		string hpStr = enemyAtk.substr(2);
    		stringstream convert;
				convert.str(hpStr);
    		convert >> dmg;

    		if(hp > 0 && dmg > 0) {
    			action = "PC deals " + to_string(dmg) + " damage to " + enemyType + "(" + to_string(hp) + " HP).";
          addAction(action);
    		} else if (hp > 0) {
    			action = "PC missed " + enemyType + ".";
      		addAction(action);
    		} else {
  				action = "PC deals " + to_string(dmg) + " damage to " + enemyType + " and kills it.";
          theGrid[pos.first][pos.second].removeEntity();
					deletedIt = it;
      		addAction(action);

          // Drop gold
          switch((*it)->getSubType()) {
					case DWARF: case ELF: case HALFLING: case ORC: {
						addAction("PC picked up " + to_string(goldDiff) + " gold.");
						break;
					}
					case HUMAN: {
						addAction("PC found 4 gold from the human's remains.");
						break;
					}
					case MERCHANT: {
						addAction("PC found 4 gold from the merchant's hoard.");
						break;
					}
					case DRAGON: {
						shared_ptr<Dragon> dragon = dynamic_pointer_cast<Dragon>(*it);
						shared_ptr<DragonHoard> hoardptr = dragon->getHoard();
						hoardptr->removeDragon();
					  // if player is on hoard
						if (lastHoard.get() == hoardptr.get()) {
							lastHoard.reset();
							ptrdiff_t index = distance(treasures.begin(), find(treasures.begin(), treasures.end(), hoardptr));
							treasures.erase(treasures.begin() + index);
							addAction("PC found 6 gold from the dragon's hoard.");
						}
						break;
					}
          }
					if (player->getSubType() == GOBLIN) addAction("PC looted 5 extra gold.");
    		}
    	}
      if((*it)->getSubType() == CharacterType::MERCHANT) {
        player->attackMerch();
      }
			if (deletedIt != enemies.end()) enemies.erase(deletedIt);
      return true;
    }
  }

  cout << "ERROR: Invalid target. There is no enemy there." << endl;
  return false;
}

// returns number of unseen potions at a position
int Grid::unknownPotionsSpotted(pair<int, int> pos) {
  int pots = 0;
  for(int y = pos.first-1; y <= pos.first+1; y++){
    for(int x = pos.second-1; x <= pos.second+1; x++){
      if((x != pos.second || y != pos.first) && x >= 0 && y >= 0 && x < WIDTH && y < BOARDHEIGHT){
         if(theGrid[y][x].getType() == Tile::ENT){
           if(theGrid[y][x].getEntityPtr()->getType() == EntityType::POTION ||
						 theGrid[y][x].getEntityPtr()->getType() == EntityType::TREASURE){
             shared_ptr<Item> item = dynamic_pointer_cast<Item>(theGrid[y][x].getEntityPtr());
             if(item->getType() == EntityType::POTION){
               shared_ptr<Potion> potion = dynamic_pointer_cast<Potion>(item);
               if(!potion->wasSeen()){
                 pots++;
               }
             }
           }
         }
      }
    }
  }
	return pots;
}

// adds moving action to queue
void Grid::addMoveAction(Direction dir, pair<int, int> pos){
  int pots = unknownPotionsSpotted(pos);
  string action = "PC moves ";
  switch(dir){
    case NO: action += "North";
    break;
    case SO: action += "South";
    break;
    case EA: action += "East";
    break;
    case WE: action += "West";
    break;
    case NE: action += "Northeast";
    break;
    case NW: action += "Northwest";
    break;
    case SE: action += "Southeast";
    break;
    case SW: action += "Southwest";
    break;
  }
	stringstream convert;
	convert << pots;  // convert pots to string
	if (pots == 1) action += " and sees an unknown potion";
  else if(pots > 1) action += " and sees " + convert.str() + " unknown potions";
  addAction(action + ".");
}

// print actions and clears vector
ostream &Grid::printAction(ostream &out) const {
	out << "Action: ";
	for (string action : actions) {
		out << action << " ";
	}
	out << endl;
  return out;
}

void Grid::clearActions(){  actions.clear(); }

// swap entities between two tiles
void Grid::swapTiles(pair<int, int> pos1, pair<int, int> pos2) {
	Tile temp = theGrid[pos1.first][pos1.second];
	theGrid[pos1.first][pos1.second] = theGrid[pos2.first][pos2.second];
	theGrid[pos2.first][pos2.second] = temp;
}

// called when game is over
void Grid::gameOver(bool win) {
	// Player won (reached floor 5)
	if (win) {
		cout << "\n\n-----------------------------------------------------------------" << endl;
		cout << "-------------------------   YOU WIN!!   -------------------------" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "--------------------------    STATS   ---------------------------" << endl;

		// print score
		cout << "Score: " << score() << endl;

		// print race
		cout << "Race: ";
		CharacterType race = player->getSubType();
		switch (race) {
		case CharacterType::SHADE: cout << "Shade ";
			break;
		case CharacterType::DROW: cout << "Drow ";
			break;
		case CharacterType::VAMPIRE: cout << "Vampire ";
			break;
		case CharacterType::TROLL: cout << "Troll ";
			break;
		case CharacterType::GOBLIN: cout << "Goblin ";
			break;
		}

		// print gold
		cout << "\nGold: " << player->getGold() << endl;

		//HP: Int
		cout << "HP: " << player->getHp() << endl;
		//Atk: Int
		cout << "Atk: " << player->getAtk() + player->getatkMod() << endl;
		//Def: Int
		cout << "Def: " << player->getDef() + player->getdefMod() << endl << endl << endl;

		quit();
	}
	// Player is dead
	else {
		cout << "\n\n-----------------------------------------------------------------" << endl;
		cout << "-------------------------   GAME OVER   -------------------------" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "--------------------------    STATS   ---------------------------" << endl;

		// print score
		cout << "Score: " << score() << endl;

		// print race
		cout << "Race: ";
		CharacterType race = player->getSubType();
		switch (race) {
		case CharacterType::SHADE: cout << "Shade ";
			break;
		case CharacterType::DROW: cout << "Drow ";
			break;
		case CharacterType::VAMPIRE: cout << "Vampire ";
			break;
		case CharacterType::TROLL: cout << "Troll ";
			break;
		case CharacterType::GOBLIN: cout << "Goblin ";
			break;
		}

		// print gold
		cout << "\nGold: " << player->getGold() << endl;

		//Atk: Int
		cout << "Atk: " << player->getAtk() + player->getatkMod() << endl;
		//Def: Int
		cout << "Def: " << player->getDef() + player->getdefMod() << endl << endl << endl;

		quit();
	}
}

// tries to move player
bool Grid::movePlayer(Direction dir) {
	// initial tile
	pair<int, int> startPos = player->getPosition();
	pair<int, int> pos = getPos(dir);

	// check if actual position
	if (pos == make_pair(-1, -1)) {
		return false;
	}

	// Get tile player is moving to
	Tile &tile = theGrid[pos.first][pos.second];

	// checks if valid tile
	if (tile.getType() == Tile::DOORWAY || tile.getType() == Tile::FLOOR || tile.getType() == Tile::PASSAGE) {
		swapTiles(startPos, pos);
		player->move(pos);

		// Put hoard back on board
		if (lastHoard) {
			pair<int, int> hPos = lastHoard->getPosition();
			theGrid[hPos.first][hPos.second].setEntity(lastHoard);
			lastHoard.reset();
		}

		// checks for any previously unseen potions within 1 block radius
		addMoveAction(dir, pos);
		return true;
	}
	// checks if tile has another entity
	else if (tile.getType() == Tile::ENT) {
		// if treasure
		if (tile.getEntityPtr()->getType() == EntityType::TREASURE) {
			// Put hoard back on board
			if (lastHoard) {
				pair<int, int> hPos = lastHoard->getPosition();
				theGrid[hPos.first][hPos.second].setEntity(lastHoard);
				lastHoard.reset();
			}

			string msg;
			shared_ptr<Item> item = dynamic_pointer_cast<Treasure>(tile.getEntityPtr());

			switch (item->getSubType()) {
			case SMALL:
				player->addGold(1);
				msg = "PC found 1 gold in the small pile.";
				break;
			case MEDIUM:
				player->addGold(2);
				msg = "PC found 2 gold in the normal gold pile.";
				break;
			case MERCHANT_HOARD:
				player->addGold(4);
				msg = "PC found 4 gold from the merchant's hoard.";
				break;
			case DRAGON_HOARD:
				shared_ptr<DragonHoard> dHoard = dynamic_pointer_cast<DragonHoard>(item);

				// if no dragon attached
				if (!(dHoard->hasDragon())) {
					player->addGold(6);
					msg = "PC found 6 gold from the dragon's hoard.";
				}
				// has dragon attached
				else lastHoard = tile.getEntityPtr();
				break;
			}
			// remove entity from tile and move player
			tile.removeEntity();
			swapTiles(startPos, pos);
			player->move(pos);
			addMoveAction(dir, pos);
			addAction(msg);
			return true;
		}
		// Stairs
		else if (tile.getEntityPtr()->getType() == EntityType::STAIRS) {
			// if last floor
			if (floor == 5) {
				gameOver(true);
				return true;
			}
			else nextFloor();

			return true;
		}
		else cout << "ERROR: Invalid move. You cannot move there." << endl;
	}
	else cout << "ERROR: Invalid move. You cannot move there." << endl;

	return false;
}

// resets game
void Grid::restart() {
	clearGrid();
  this->floor = 0;
  enemiesMove = true;

  theGrid = vector<vector<Tile>>(BOARDHEIGHT);
  player = make_shared<Player>();
}

// adds action to queue
void Grid::addAction(string s) { actions.push_back(s); }

bool compareEnemyPtr(shared_ptr<Enemy> a, shared_ptr<Enemy> b) {return (*a < *b);}

// makes enemy turns
void Grid::enemyTurn() {
    sort(enemies.begin(), enemies.end(), compareEnemyPtr);
  for (auto enemy: enemies){
		pair<int, int> enemyPos = enemy->getPosition();

		string enemyAtk;
		// if Dragon
		if (enemy->getSubType() == CharacterType::DRAGON) {
			shared_ptr<Dragon> dragon = dynamic_pointer_cast<Dragon>(enemy);
			// checks if player is adjacent to dragon or hoard
			if (isAdjacent(dragon->getPosition(), player->getPosition()) || isAdjacent(dragon->getHoard()->getPosition(), player->getPosition())){
                enemyAtk = enemy->attack(player);
                string action;
    			string enemyType = string(1, enemyAtk[0]);

    			int dmg;
    			string dmgStr = enemyAtk.substr(2);  // dmg dealt

    			// convert dmgStr to int
    			stringstream convert;
    			convert.str(dmgStr);
    			convert >> dmg;

    			if (dmg > 0)  action = enemyType + " deals " + dmgStr + " damage to PC.";
    			else action = enemyType + " missed PC.";
    			// TODO
    			addAction(action);
            }
		}
		// Move
		else if (!isAdjacent(enemyPos, player->getPosition()) || (enemy->getSubType() == CharacterType::MERCHANT && !(player->hasAttackedMerch()))) {
			if (enemiesMove) {
				vector<pair<int, int>> emptyPositions = getEmptyNeighbours(enemyPos);
				if (emptyPositions.size() > 0) {
					// Load RNG
					int rng = rand() % emptyPositions.size();
					swapTiles(enemy->getPosition(), emptyPositions[rng]);
					enemy->move(emptyPositions[rng]);
				}
			}
			else continue;
		}
		// Attack
		else {
			// retrieves results of attack
			enemyAtk = enemy->attack(player);

			string action;
			string enemyType = string(1, enemyAtk[0]);

			int dmg;
			string dmgStr = enemyAtk.substr(2);  // dmg dealt

			// convert dmgStr to int
			stringstream convert;
			convert.str(dmgStr);
			convert >> dmg;

			if (dmg > 0)  action = enemyType + " deals " + dmgStr + " damage to PC.";
			else action = enemyType + " missed PC.";
			// TODO
			addAction(action);
		}
  }
  if(player->getHp() == 0){
      gameOver(false);
  }
}

// calculate end-of-game score
int Grid::score() {
  int score = player->getGold();
  if(player->getSubType() == CharacterType::SHADE){
      score = score * 3 /2;
  }
  return score;
}

/* DURING GAME */

// creates player via user input
void Grid::newPlayer(){
	string line;

  // Prompt
  cout << "Choose your character:\n\n";
  cout << "s - Shade\n";
  cout << "d - Drow\n";
  cout << "v - Vampire\n";
  cout << "t - Troll\n";
  cout << "g - Goblin\n";
  cout << "Enter choice: ";

  CharacterType race;
  string cmd;
  while(cin >> cmd) {
    if(cmd == "s") race = SHADE;
    else if(cmd == "d") race = DROW;
    else if(cmd == "v") race = VAMPIRE;
    else if(cmd == "t") race = TROLL;
    else if(cmd == "g") race = GOBLIN;
    else {
			cout << "ERROR: Invalid choice.  Please select a valid number.\nEnter choice: ";
			continue;
    }
		cout << endl << endl;
    setPlayer(race);
    break;
  }
}

// initialize player
void Grid::setPlayer(CharacterType type) { player = dynamic_pointer_cast<Player>(CharacterSpawner::createEntity(type)); }

// generate new floor via RNG
void Grid::genFloor() {
  // GENERATE
  // -> Player
  int playerChamber = rand() % chambers.size();
  pair<int, int> pos = getEmptyTile(playerChamber, false);
  player->setPosition(pos);
  theGrid[pos.first][pos.second].setEntity(player);

  // -> Stairs
	StairsSpawner ss;
  int stairsChamber = rand() % chambers.size();
  while(playerChamber == stairsChamber){
    stairsChamber = rand() % chambers.size();
  }
  pos = getEmptyTile(stairsChamber, false);
	shared_ptr<Entity> e = ss.spawn(pos);
  theGrid[pos.first][pos.second].setEntity(e);

  // -> Potions
	// -> 10 potions
	for (int i = 0; i < 10; i++) {
		int rng = rand() % 6;
		int chamber = rand() % chambers.size();
		pos = getEmptyTile(chamber, false);
		shared_ptr<Potion> pot = dynamic_pointer_cast<Potion>(charToEntity('0' + rng, pos.first, pos.second));
		potions.push_back(pot);
		theGrid[pos.first][pos.second].setEntity(pot);
	}

  // -> Treasure
	// -> 10 treasures
	for (int i = 0; i < 10; i++) {
		shared_ptr<Treasure> treasure;
		int rng = rand() % 8;
		int chamber = rand() % chambers.size();
		pair<int, int> pos = getEmptyTile(chamber, rng > 6);  // get valid empty tile (second arg is true if DragonHoard)
		// Small Hoard
		if (rng <= 4) treasure = dynamic_pointer_cast<Treasure>(charToEntity('6', pos.first, pos.second));
		// Medium Hoard
		else if (rng <= 6) treasure = dynamic_pointer_cast<Treasure>(charToEntity('7', pos.first, pos.second));
		// Dragon Hoard
		else {
			shared_ptr<DragonHoard> dHoard = dynamic_pointer_cast<DragonHoard>(charToEntity('9', pos.first, pos.second));
			pair<int, int> dPos = findEmptyNeighbour(pos);  // get position of empty neighbour of hoard
			shared_ptr<Dragon> dragon = dynamic_pointer_cast<Dragon>(charToEntity('D', dPos.first, dPos.second));
			enemies.push_back(dragon);

			dragon->setHoard(dHoard);
			dHoard->setDragon(dragon);

			theGrid[dPos.first][dPos.second].setEntity(dragon);
			treasure = dHoard;
		}
		treasures.push_back(treasure);
		theGrid[pos.first][pos.second].setEntity(treasure);
	}

  // -> Enemies
	// -> 20 enemies
	for (int i = 0; i < 20; i++) {
		int rng = rand() % 18;
		int chamber = rand() % chambers.size();
		pair<int, int> pos = getEmptyTile(chamber, false);
		shared_ptr<Entity> enemy;
		if (rng <= 3) enemy = charToEntity('H', pos.first, pos.second);
		else if (rng <= 6) enemy = charToEntity('W', pos.first, pos.second);
		else if (rng <= 11) enemy = charToEntity('L', pos.first, pos.second);
		else if (rng <= 13) enemy = charToEntity('E', pos.first, pos.second);
		else if (rng <= 15) enemy = charToEntity('O', pos.first, pos.second);
		else enemy = charToEntity('M', pos.first, pos.second);

		enemies.push_back(dynamic_pointer_cast<Enemy>(enemy));
		theGrid[pos.first][pos.second].setEntity(dynamic_pointer_cast<Enemy>(enemy));
	}
}

// assign hoards to dragons
// ASSUMPTION:  obvious which hoard belongs to which dragon
void assignHoards(vector<shared_ptr<Dragon>> dragons, vector<shared_ptr<DragonHoard>> hoards) {
	for (shared_ptr<Dragon> dragon : dragons) {
		unsigned int j = 0;
		for (unsigned int i = 0; i < hoards.size(); i++) {
			// assign dragon and hoard to each other
			if (isAdjacent(dragon->getPosition(), hoards[i]->getPosition())) {
				dragon->setHoard(hoards[i]);
				hoards[i]->setDragon(dragon);
				j = i;
			}
		}
		if(j < hoards.size()) hoards.erase(hoards.begin() + j);  // remove element from hoards vector
	}
	if (hoards.size() > 0) {
		cout << "ERROR: Invalid allocation of dragon hoards.\nPress any key to exit.";
		exit(1);
	}
}

// loads next floor
void Grid::nextFloor() {
	floor++;
	clearGrid();

	if (floor == 1) addAction("Player character has spawned.");
	else addAction("Advanced to next floor.");

	// load next floor from string vector
	for (int r = (floor - 1) * BOARDHEIGHT; r < floor * BOARDHEIGHT; r++) {
        stringToRow(map[r], r - (floor - 1) * BOARDHEIGHT);
	}
	// get coordinates of top-left corner of next unassigned chamber
	pair<int, int> chamberStart = getChamberStart(2, 2);
	int chamberNum = 1;
	while (chamberStart.first != -1) {
		vector<pair<int, int>> row;
		chambers.push_back(row);
		int r = chamberStart.first;
		int c = chamberStart.second;
		// populate chamber with chamberNum and return end of chamber
		c = assignChamber(chamberNum, r, c);
		chamberNum++;
		chamberStart = getChamberStart(r, c);
	}

    // resets all buffs/debuffs
    player->resetMod();

	if (isDefaultMap) genFloor();
    else {
    	// Retrieve dragons and dragon hoards
    	vector<shared_ptr<Dragon>> dragons;
    	for (shared_ptr<Entity> enemy : enemies) {
    		shared_ptr<Enemy> d = dynamic_pointer_cast<Enemy>(enemy);
    		if (d->getSubType() == DRAGON) dragons.push_back(dynamic_pointer_cast<Dragon>(enemy));
    	}
    	vector<shared_ptr<DragonHoard>> hoards;
    	for (shared_ptr<Treasure> hoard : treasures) {
    		if (hoard->getSubType() == DRAGON_HOARD) hoards.push_back(dynamic_pointer_cast<DragonHoard>(hoard));
    	}

    	// assign hoards to dragons
    	assignHoards(dragons, hoards);
    }
}

// load blank grid
void Grid::loadGrid() {
  // input base floor
  string fname = "src/Grids/emptygrid.txt";
  ifstream file (fname.c_str());

  if (!file) {
    cerr << "ERROR: Incorrect filename. Press a button to continue..." << endl;

		string temp;
		cin >> temp;
    exit(1);
  }

	isDefaultMap = true;
  loadGrid(file);
}

// load grid from file
void Grid::loadGrid(ifstream &stream) {
  if(!stream) {
    cout << "ERROR: Unable to open file!";
    exit(1);
  }

	string line;
	while (getline(stream, line)) {
		map.push_back(line);
	}
	stream.close();
}

// closes program
void Grid::quit() {
	clearGrid();
	theGrid.clear();
	cout << "Press any key to exit." << endl;
	string temp;
	cin >> temp;
	exit(0);
}

ostream &operator<<(ostream &out, const Grid &g) {
  // Print contents of theGrid
	for (unsigned int r = 0; r < g.theGrid.size(); r++) {
		vector<Tile> row = g.theGrid[r];
		for (unsigned int c = 0; c < row.size(); c++) {
      shared_ptr<Entity> e = row[c].getEntityPtr();
			if (e.get() == nullptr) out << row[c];  // no entity
			else out << *(e.get());  // entity on floor tile
		}
		out << endl;
	}
  // print race
	out << "Race: ";
  CharacterType race = g.player->getSubType();
  switch(race){
    case CharacterType::SHADE: out << "Shade ";
    break;
    case CharacterType::DROW: out << "Drow ";
    break;
    case CharacterType::VAMPIRE: out << "Vampire ";
    break;
    case CharacterType::TROLL: out << "Troll ";
    break;
    case CharacterType::GOBLIN: out << "Goblin ";
    break;
  }
  // print gold
  out << "Gold: ";
  int gold = g.player->getGold();
  out << gold;
  // right indent
  for(int i = 0; i < 51; i++) out << " ";
  // print floor number
  out << "Floor " << g.floor << endl;

  //HP: Int
  out << "HP: " << g.player->getHp() << endl;
  //Atk: Int
  out << "Atk: " << max(g.player->getAtk() + g.player->getatkMod(), 0); << endl;
  //Def: Int
  out << "Def: " << max(g.player->getDef() + g.player->getdefMod(), 0); << endl;

  // display actions
  g.printAction(out);
  return out;
}
