#ifndef SHIP_H
#define SHIP_H

#include "Random.h"
#include "Colour.h"

// The Ship class creates ship with coordinates and changes their status, also checks collision of two ships. It gives information about the ship.


using std::cout, std::cin, std::endl,
std::setw, std::string, std::vector;
using vec = vector<string>;
using mat = vector<vec>;
using vec2 = vector<class Ship>;


class Ship
{
public:
	int len{};
	int dir{};
	int ship_lost{};	// Is ship sunken?
	mat coordinates{}; // coordinates[0] - x; coordinates[1] - y; coordinates[2] - status;

	Ship() {
		cout << "\nCan't generate ship without its length";
	}

	Ship(int length) {

		int x{}, y{};
		len = length;

		if (len > 1) {
			cout << "\nHow do you want to set " << len << "-length ship? (1 - vertically | 2 - horizontally): ";
			cin >> dir;
			while (cin.fail()) {
				cin.clear();
				cin.ignore();
				SetC(12);
				cout << "Please enter an integer" << endl;
				SetC(7);
				cin >> dir;
			}
		}
		else {
			dir = 1;
			cout << "\nSetting 1-length ship...";
		}

		//Choosing direction and creates whole ship starting from chosen coordinates.

		while (1) {


			cout << "\nEnter x: ";
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

			if (dir == 1) {

				if (y + len - 1 > 10) {
					cout << "\nError, ship will not fit\n";
					continue;
				}

				mat pom(2, vec(len, std::to_string(x)));

				for (int i = 0; i < len; i++) {
					pom[1][i] = std::to_string(y + i);
				}

				coordinates = pom;
				coordinates.push_back(vec(len, "H"));	//adding status to coordinates
				break;
			}

			else if (dir == 2) {

				if (x + len - 1 > 10) {
					cout << "\nError, ship will not fit\n";

					continue;
				}

				mat pom(2, vec(len, std::to_string(y)));

				for (int i = 0; i < len; i++) {
					pom[0][i] = std::to_string(x + i);
				}

				coordinates = pom;
				coordinates.push_back(vec(len, "H"));	//adding status to coordinates
				break;
			}
			else {
				cout << "\nYou entered wrong direction, please try again (1 - vertically | 2 - horizontally): ";

				cin >> dir;
				while (cin.fail()) {
					cin.clear();
					cin.ignore();
					SetC(12);
					cout << "Please enter an integer" << endl;
					SetC(7);
					cin >> dir;
					system("cls");
				}

				continue;
			}

		}

	}

	Ship(int length, string s) {

		int x{}, y{};
		len = length;

		dir = RandN(1, 2);

		//Draw the direction and create the whole ship starting from randomly selected coordinates.

		while (1) {


			x = RandN(1, 10);

			y = RandN(1, 10);

			if (x > 10 || x < 1 || y > 10 || y < 1) {
				continue;
			}

			if (dir == 1) {

				if (y + len - 1 > 10) //Error, ship will not fit
					continue;

				mat pom(2, vec(len, std::to_string(x)));

				for (int i = 0; i < len; i++) {
					pom[1][i] = std::to_string(y + i);
				}

				coordinates = pom;
				coordinates.push_back(vec(len, s)); //adding status to coordinates
				break;
			}

			else if (dir == 2) {

				if (x + len - 1 > 10) //Error, ship will not fit
					continue;


				mat pom(2, vec(len, std::to_string(y)));

				for (int i = 0; i < len; i++) {
					pom[0][i] = std::to_string(x + i);
				}

				coordinates = pom;
				coordinates.push_back(vec(len, s)); //adding status to coordinates
				break;
			}


		}

	}

	int GetX(int j);
	int GetY(int j);
	int Check();
	string GetStatus(int j);
	int CheckCollision(vec2 ships, bool random);
	int ChangeStatus(int x, int y);

};


#endif

