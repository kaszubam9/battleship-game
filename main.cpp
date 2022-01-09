/*

	Battleship Game
	Author: Michal Kaszuba
	Email:  mkaszuba09@gmail.com
	Latest update: 04.01.2022

*/

#include "Game.h"

int main() {

	int c;
	SetC(14);
	cout << "\n\nWelcome to Battleship Game!\n";


	while (true) {

		SetC(10);
		cout << "\n1 - Play";
		SetC(12);
		cout << "\n2 - Quit\n";
		SetC(7);
		cin >> c;

		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			SetC(12);
			cout << "Please enter an integer" << endl;
			SetC(7);
			cin >> c;
		}

		if (c == 1) {
			c = 0;
			Game g;
		}
		else if (c == 2) {
			break;
		}
		else if (c == 0) {
			continue;
		}
		else {
			system("cls");
			cout << "\nWrong number!\n";
			continue;
		}
	}

	system("cls");
	SetC(2);
	cout << "\nGoodbye!\n";
	SetC(7);
	return 0;
}