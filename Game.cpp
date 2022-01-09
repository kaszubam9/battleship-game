#include "Game.h"

void Game::Info() {					// Prints info
	int temp = 10;
	while (temp > 0) {
		system("cls");
		SetC(7);
		cout << "Legend: \n";
		SetC(10);
		cout << "H - Healthy\n";
		SetC(12);
		cout << "D - Damaged\n";
		SetC(8);
		cout << "X - Sunken\n";
		SetC(11);
		cout << "O - Miss\n\n";

		if (fog_of_war) {
			SetC(5);
			cout << "Fog of war is enabled\n\n";
			SetC(7);
			cout << "Enter 1 to disable.\nEnter 0 to go back.\n";
		}
		else {
			SetC(5);
			cout << "Fog of war is disabled\n\n";
			SetC(7);
			cout << "Enter 2 to enable.\nEnter 0 to go back.\n";
		}

		cin >> temp;

		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			SetC(12);
			cout << "Please enter an integer" << endl;
			SetC(7);
			cin >> temp;
		}

		if (temp == 2)
			fog_of_war = true;
		else if (temp == 1)
			fog_of_war = false;

	}
}


bool Game::CheckScore() {		// Checks score and gives winner if all ships on one side sunk


	if (enemy.GetPoints() == enemy.ships.size()) {
		winner = 1;
		return false;
	}
	else if (player.GetPoints() == player.ships.size()) {
		winner = 0;
		return false;
	}
	else
		return true;
}

void Game::PrintGame() {			// Prints players' boards

	player.PlaceShips();
	enemy.PlaceShips();

	system("cls");
	SetC(6);
	cout << "\nYour board\n\n";
	player.PrintBoard(false);
	SetC(12);
	cout << "\n\nEnemy board\n\n";
	enemy.PrintBoard(fog_of_war);
	SetC(7);
}


int Game::Fire() {				// Player shoots on target
	int x{};
	int y{};

	cout << "\n\nPlayer Turn, choose target coordinates:";

	while (1) {
		cout << "\nEnter x : ";
		cin >> x;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			SetC(12);
			cout << "Please enter an integer" << endl;
			SetC(7);
			cin >> x;
		}

		cout << "\nEnter y: ";
		cin >> y;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			SetC(12);
			cout << "Please enter an integer" << endl;
			SetC(7);
			cin >> y;
		}

		if (x > 10 || x < 1 || y > 10 || y < 1) {
			cout << "\nWrong coordinates\n";
			continue;
		}
		else
		{
			if (enemy.board[y][x] == "O" || enemy.board[y][x] == "X" || enemy.board[y][x] == "D") {
				cout << "\nYou have already hit there, try another coordinates.\n";
				continue;
			}
			else
				break;
		}
	}

	for (int i = 0; i < enemy.ships.size(); i++) {
		if (enemy.ships[i].ChangeStatus(x, y)) {
			SetC(14);
			cout << "\nHit!\n";
			SetC(7);
			Sleep(1700);
			return 1;
		}
	}
	SetC(4);
	cout << "\nMiss!\n";
	SetC(4);
	enemy.board[y][x] = "O";
	Sleep(1700);
	return 0;
}

int Game::EnemyFire() {							// Enemy shoot on target
	cout << "\n\nEnemy turn, take cover!\n";
	Sleep(2000);

	int x{};
	int y{};


	while (1) {

		x = RandN(xmin, xmax);					// Randomly picking target from [1-10][1-10], if enemy hit, range will decrease, when whole ship sink - range goes back to 1-10
		y = RandN(ymin, ymax);

		if (x > 10 || x < 1 || y > 10 || y < 1) { // Checks if coordinates are correct;
			continue;
		}

		else {
			if (player.board[y][x] == "O" || player.board[y][x] == "X" || player.board[y][x] == "D") {
				if (hit) {						// When enemy hit and then miss on neighbouring X coordinates, he will change shooting to Y-axis, condition 10 is for certainty
					streak++;
					if (streak > 10 && streak < 30) {
						xmin = tempx; xmax = tempx; ymin = tempy - 1; ymax = tempy + 1;
					}
					if (streak > 30 && streak < 60) {		// Extend range if there is no free coordinate in current range on X-axis 
						xmin = tempx; xmax = tempx; ymin = tempy - 2; ymax = tempy + 2;
					}
					if (streak > 60 && streak < 90) {		// Extend range if there is no free coordinate in current range on Y-axis 
						xmin = tempx - 2; xmax = tempx + 2; ymin = tempy; ymax = tempy;
					}
					if (streak > 90) {		// I give up, i will find you later..
						xmin = 1; xmax = 10; ymin = 1; ymax = 10;
						hit = 0;
						streak = 0;
					}
				}
				continue;
			}
			else
				break;
		}

	}

	for (int i = 0; i < player.ships.size(); i++) {
		if (player.ships[i].ChangeStatus(x, y) == 1) {		// Check if one of the ship have been hit.
			SetC(4);
			cout << "\nEnemy hits!\n";
			hit = 1;

			tempx = x;
			tempy = y;

			if (player.ships[i].ship_lost == 0) {  // Improves enemy accuracy

				if (streak > 10) {
					xmin = tempx; xmax = tempx; ymin = tempy - 1; ymax = tempy + 1; // Missing 2 times on X-axis will make the enemy try only on Y-axis
				}
				else {
					xmin = x - 1; xmax = x + 1; ymin = y; ymax = y;     // After enemy's hit, it will look for next target in X-axis, with minimum distance from current target
				}
			}
			else {
				xmin = 1; xmax = 10; ymin = 1; ymax = 10;
				hit = 0;
				streak = 0;
			}

			SetC(7);
			Sleep(1700);
			return 1;
		}
	}
	SetC(14);
	cout << "\nEnemy misses!\n";

	SetC(7);
	player.board[y][x] = "O";
	Sleep(1700);
	return 0;
}

