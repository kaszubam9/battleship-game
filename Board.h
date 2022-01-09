#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"

//The Board class creates vector of ships - randomly or manually by user and places it on a created board and prints it. It is also responsible for getting current score.

class Board
{

public:
	mat board;
	vec2 ships;

	Board() {   // creating an empty board

		mat pom(11, vec(11, "-"));


		for (int i = 0; i < pom.size(); i++) {
			pom[i][0] = std::to_string(i);
			pom[0][i] = std::to_string(i);
		}
		pom[0][0] = "Y/X";
		board = pom;

	}


	void PrintBoard(bool fog_of_war);
	void CreateShips();
	void CreateRandomShips();
	void PlaceShips();
	int GetPoints();
};

#endif