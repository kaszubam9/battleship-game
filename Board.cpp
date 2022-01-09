#include "Board.h"
#include <Windows.h>

int Board::GetPoints() {   //Returns sum of sunken ships
	int points{};
	for (int i = 0; i < ships.size(); i++) {
		points += ships[i].Check();
	}
	return points;
}

void Board::PrintBoard(bool fog_of_war) {

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {


			if (board[i][j] == "H")			// Color setting 
				SetC(10);
			else if (board[i][j] == "D")
				SetC(12);
			else if (board[i][j] == "X")
				SetC(8);
			else if (board[i][j] == "O")
				SetC(11);
			else if (board[i][j] == "-")
				SetC(1);
			else
				SetC(15);

			if (fog_of_war && board[i][j] == "H") {	// If fog_of_war is enabled, then hide enemy's ships
				SetC(1);
				cout << setw(3) << "-" << " ";

			}
			else
				cout << setw(3) << board[i][j] << " ";

		}
		cout << endl;
	}
	SetC(7);
}

void Board::CreateShips() {				//Creates 10 ships: 1 - 4-length; 2 - 3-length; 3 - 2-length; 4 - 1 length;
	vec2 pom{};
	int l[10]{ 4,3,3,2,2,2,1,1,1,1 };

	for (int i = 0; i < 10; i++) {
		Ship s(l[i]);

		if (i > 0 && s.CheckCollision(pom, false) == 1) {	 //Go back, when collision
			i--;
			system("cls");
			PrintBoard(false);
			continue;
		}

		pom.push_back(s);
		ships = pom;
		PlaceShips();
		system("cls");
		PrintBoard(false);
	}


}

void Board::CreateRandomShips() {			// Creates random ships
	cout << "\nGenerating random ships, please wait...\n";
	Sleep(1200);
	vec2 pom{};
	int l[10]{ 4,3,3,2,2,2,1,1,1,1 };

	for (int i = 0; i < 10; i++) {
		Ship s(l[i], "H");

		if (i > 0 && s.CheckCollision(pom, true) == 1) {		// Collision - go back
			i--;
			continue;
		}
		pom.push_back(s);
	}
	ships = pom;
}

void Board::PlaceShips() {			//Places ships on the board;

	for (int i = 0; i < ships.size(); i++) {
		for (int j = 0; j < ships[i].len; j++) {
			board[ships[i].GetY(j)][ships[i].GetX(j)] = ships[i].GetStatus(j);
		}

	}
}