#ifndef GAME_H
#define GAME_H

#include"Board.h"

//The Game class is responsible for creating the game and running it


class Game
{
public:
	int score{};
	int winner{};

	Board player;
	Board enemy;

	bool fog_of_war;
	bool player_turn;

	int xmax{}, xmin{}, ymax{}, ymin{}, tempx{}, tempy{}; //these integers help the computer with accuracy 
	int streak, hit;

	Game() {
		xmin = 1; xmax = 10; ymin = 1; ymax = 10;
		player_turn = false;
		fog_of_war = true;
		streak = 0;
		hit = 0;
		int choice{};

		while (1) {
			system("cls");		//Menu
			SetC(9);
			cout << "\n1 - Place ships manually";
			SetC(2);
			cout << "\n2 - Place ships randomly";
			SetC(14);
			cout << "\n3 - Info";
			SetC(4);
			cout << "\n4 - Nevermind...\n";
			SetC(7);

			cin >> choice;
			while (cin.fail()) {
				cin.clear();
				cin.ignore();
				SetC(12);
				cout << "Please enter an integer" << endl;
				SetC(7);
				cin >> choice;
			}

			switch (choice) {
			case 1:
				player.PrintBoard(false);
				player.CreateShips();

				break;
			case 2:
				player.CreateRandomShips();

				break;
			case 3:
				Info();
				continue;
			case 4:
				cout << "\nLet's try again!\n";
				break;
			default:
				cout << "\nWrong integer!";
				continue;
			}

			break;
		}

		if (choice == 1 || choice == 2) {

			cout << "\nCreating enemy ships...";
			enemy.CreateRandomShips();

			system("cls");
			SetC(11);

			if (RandN(0, 1)) {				//Randomly picking the starting side
				player_turn = true;
				cout << "\nPlayer starts\n";
			}
			else
				cout << "\nEnemy starts\n";
			SetC(13);
			cout << "\n################\n";
			cout << "\n  So it begins  \n";
			cout << "\n################\n";
			Sleep(4000);
			SetC(7);
			while (CheckScore()) {

				PrintGame();

				if (player_turn) {
					if (!Fire())
						player_turn = false;			//Methods Fire() and EnemyFire() return 0 when you miss, turn goes to another player.

				}
				else {
					if (!EnemyFire())
						player_turn = true;
				}

			}


			if (winner == 1) {

				PrintGame();
				SetC(6);
				cout << "\n\n#######################################\n" << endl;
				cout << "You have won the game! Congratulations!\n" << endl;
				cout << "#######################################" << endl;
			}

			if (winner == 0) {

				PrintGame();
				SetC(4);
				cout << "\n\n############################################\n" << endl;
				cout << "           You have lost the game!          " << endl;
				cout << "No worries, repair your ships and try again!\n" << endl;
				cout << "############################################" << endl;
			}

		}
		SetC(7);
	}

	bool CheckScore();
	int EnemyFire();
	int Fire();
	void PrintGame();
	void Info();

};

#endif