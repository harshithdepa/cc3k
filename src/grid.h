#pragma once
#include <iostream>
#include <utility>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include "Entities/Characters/Players/player.h"
#include "Entities/Characters/Enemies/enemy.h"
#include "directions.h"

class Tile;
class Potion;
class Treasure;
class DragonHoard;

class Grid {
	const int WIDTH = 79, DISPLAYHEIGHT = 30, BOARDHEIGHT = 25;
	int floor;
	bool enemiesMove;
	std::shared_ptr<Entity> lastHoard;
	bool isDefaultMap = false;  // true if not reading in map from user
	std::vector<std::string> map; // store map read
	std::vector<std::string> actions;  // vector of actions for the turn
	int streamPos = 0;  // stores current position of stream
	const std::pair<int, int> DIMENSIONS = std::make_pair(WIDTH, DISPLAYHEIGHT);  // dimensions of grid (WIDTH, HEIGHT); last 5 rows reserved for displaying info
	std::vector<std::vector<Tile>> theGrid;  // The actual grid.
	std::vector<std::vector<std::pair<int,int>>> chambers; // Vector of vector of locations (row, column) OR (y, x)
	std::shared_ptr<Player> player;    // Player
	std::vector<std::shared_ptr<Enemy>> enemies; // Vector of enemies,
	std::vector<std::shared_ptr<Potion>> potions; // Vector of potions,
	std::vector<std::shared_ptr<Treasure>> treasures;   // Vector of treasures
	std::shared_ptr<Entity> charToEntity(char ch, int r, int c);  // converts character to entity
	std::vector<std::pair<int, int>> getEmptyNeighbours(std::pair<int, int> pos);
	std::pair<int, int> findEmptyNeighbour(std::pair<int, int> pos);
	bool hasEmptyNeighbour(std::pair<int, int> pos);
	std::pair<int, int> getEmptyTile(int chamberNum, bool dragonHoard);  // returns an empty tile in specific chamber
	int assignChamber(int n, int r, int c); // assgns chamber number to floor tiles
	std::pair<int, int> getChamberStart(int r, int c); // retrieves start of next chamber
	std::pair<int, int> getPos(Direction dir);
	int unknownPotionsSpotted(std::pair<int, int> pos); // returns number of unseen potions at a position
	void swapTiles(std::pair<int, int> pos1, std::pair<int, int> pos2);  // swap tiles
	void addMoveAction(Direction dir, std::pair<int, int> pos); // adds moving action to queue
	void stringToRow(std::string line, int r); // parse map from string
	void clearGrid();   // Frees the grid.

public:
	Grid();
	~Grid();

	void toggleEnemyMove();  // toggle movement of enemies
	std::string usePotion(Direction dir);  // use potion in specified direction
	bool attack(Direction dir);  // attack enemy in specified direction
	bool movePlayer(Direction dir);  // moves player
	void restart(); // resets game
	void clearActions();
	void addAction(std::string s);
	std::ostream &printAction(std::ostream &out) const;
	void enemyTurn(); // make enemy turns
	int score(); // calculate end-of-game score

	void newPlayer(); // creates player via user input
	void setPlayer(CharacterType type); // initialize player
	void genFloor(); // Generate new floor via RNG
	void nextFloor();  // loads next floor
	void loadGrid(); // Load blank grid
	void loadGrid(std::ifstream &stream); // load grid from text file
	void gameOver(bool win); // Call when game is over
	void quit(); // end of game

	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};
