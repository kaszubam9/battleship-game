#include "Ship.h"
#include <Windows.h>

int Ship::GetX(int j) {						// Returns value x of j-fragment of ship
	return std::stoi(coordinates[0][j]);
}

int Ship::GetY(int j) {						// Returns value y of j-fragment of ship
	return std::stoi(coordinates[1][j]);
}

int Ship::Check() {							// Check if ship is sunk
	return ship_lost;
}

string Ship::GetStatus(int j) {				// Returns the state of j-fragment of ship
	return coordinates[2][j];
}

int Ship::ChangeStatus(int x, int y) {		// Ship under attack
	int hit{};

	if (dir == 1) {		// Checking by direction
		if (x == GetX(0)) {
			for (int i = 0; i < len; i++) {			// Hit on target - change state of coordinates to damaged
				if (coordinates[1][i] == std::to_string(y)) {
					coordinates[2][i] = "D";
					hit = 1;
				}

			}
		}
	}
	else {
		if (y == GetY(0)) {
			for (int i = 0; i < len; i++) {			// Hit on target - change state of coordinates to damaged
				if (coordinates[0][i] == std::to_string(x)) {
					coordinates[2][i] = "D";
					hit = 1;						// ch
				}
			}
		}
	}

	int count{};

	for (int i = 0; i < len; i++) {					// Check how many fragments are damaged
		if (coordinates[2][i] == "D") {
			count++;
		}
	}

	if (count == len) {								// If whole fragments are damaged - change their state to sunken 
		for (int i = 0; i < len; i++) {
			coordinates[2][i] = "X";
		}
		ship_lost++;								// Abandon the ship!

	}

	return hit;		// return 0 whem miss and 1 when hit

}

int Ship::CheckCollision(vec2 ships, bool random) {		// Major rule - ships cant be adjacent to each other, this method checks if they are genereted correctly

	for (int i = 0; i < ships.size(); i++) {
		for (int j = 0; j < len; j++) {
			for (int k = 0; k < ships[i].len; k++) {
				if (abs(GetX(j) - ships[i].GetX(k)) < 2 && abs(GetY(j) - ships[i].GetY(k)) < 2) { //If the distance between two coordinates is lower than 2, two ships are adjacent to each other which is forbidden
					if (!random) {						// Don't print an error if it is random creating
						cout << "\nCollision! Place the ship again.\n";
						Sleep(2000);
					}
					return 1;							// Return 1 if there is collision and try again
				}
			}
		}
	}
	return 0;		// no collision, you can continue
}

