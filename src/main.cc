#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include "grid.h"
#include "Entities/Characters/character.h"
using namespace std;

// get direction from string
Direction getDir(string s) {
	Direction dir;
	if (s == "no") dir = NO;
	else if (s == "so") dir = SO;
	else if (s == "ea") dir = EA;
	else if (s == "we") dir = WE;
	else if (s == "ne") dir = NE;
	else if (s == "nw") dir = NW;
	else if (s == "se") dir = SE;
	else if (s == "sw") dir = SW;
	return dir;
}

int main(int argc, char *argv[]) {
	string s, fname;
	Grid g;
	bool fromFile = (argc == 2);
	// Load RNG
	srand(static_cast<unsigned int>(time(NULL)));

	if (fromFile) {
		fname = argv[1];

		// input file
		ifstream file(fname.c_str());
		if (!file) {
			cerr << "Something bad happened: perhaps incorrect filename." << endl;
			exit(1);
		}
		g.loadGrid(file);
	}
	else g.loadGrid();

	g.newPlayer();
	g.nextFloor();

	cout << "---------------------   WELCOME TO CC3000   ---------------------" << endl;
	cout << "------------------------    GAME START   ------------------------" << endl;
	cout << "\nCommand list:" << endl;
	cout << "Move player in specified direction: no,so,ea,we,ne,nw,se,sw" << endl;
	cout << "Use potion indicated by direction: u <direction>" << endl;
	cout << "Attack enemy in specified direction (1 block radius): a <direction>" << endl;
	cout << "Stop enemies from moving: f" << endl;
	cout << "Restart game: r" << endl;
	cout << "Quit game: q" << endl;
	cout << g;
	g.clearActions();
	cout << "\nEnter command: ";

	// command interpreter
	string command;
	while (cin >> command) {
		// Quit or EOF (Ctrl-D)
		if (command == "q" || cin.eof()) g.quit();

		// game commands
		vector<string> directions{ "no", "so", "ea", "we", "ne", "nw", "se", "sw" };

		if (command == "r") {

			// reset grid
			g.restart();

			if(!fromFile) g.loadGrid();
			else {
				// input file
				ifstream file(fname.c_str());
				if (!file) {
					cerr << "Something bad happened: perhaps incorrect filename." << endl;
					exit(1);
				}
			}
			g.newPlayer();
			g.nextFloor();
			cout << g;
			g.clearActions();
			cout << endl;
			cout << "Enter command: ";
			continue;

		}

		// move player
		else if (find(directions.begin(), directions.end(), command) != directions.end()) {
			if(!g.movePlayer(getDir(command))) {
				cout << "Enter command: ";
				continue;
			}
		}
		else if (command == "f") {
			g.toggleEnemyMove();
			cout << "Enter command: ";
			continue;
		}
		else if (command == "u" || command == "a") {
			string dir;
			cin >> dir;

			if (find(directions.begin(), directions.end(), dir) == directions.end()) {
				cout << "ERROR: Invalid direction.\nEnter command: ";
				continue;
			}

			// USE POTION
			if (command == "u") {
				string potType = g.usePotion(getDir(dir));
				if (potType == "") continue;
				else g.addAction("PC used " + potType + ".");
			}
			// ATTACK
			else if (command == "a") {
				if (!g.attack(getDir(dir))) {
					cout << "Enter command: ";
					continue;
				}
			}
		}
		else {
			cout << "ERROR: Invalid choice.\nEnter command: ";
			continue;
		}

		// Make enemies do stuff
		g.enemyTurn();

		// Print grid
		cout << g;
		g.clearActions();
		cout << "\nEnter command: ";
	}
}
