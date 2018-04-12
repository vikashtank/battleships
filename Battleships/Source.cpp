// classes example
#include <iostream>
#include <string>
using namespace std;

enum direction {
	horizontal, vertical
};


class SpaceShip {


public:
	int width, height;
	SpaceShip(int width, int height);
	void showSpaceShip() {

		for (int x = 0; x < (height); x++) {
			for (int x = 0; x < (width); x++) {
				cout << "S ";
			}
			cout << " " << endl;
		}


	}

};


SpaceShip::SpaceShip(int xEnd, int yEnd) {
	width = xEnd;
	height = yEnd;
}


class Board {


	string **BoardArray;
public:
	string boardID;
	int width, height;
	Board(string ID, const int x, const int y);


	void showBoard() {
		cout << boardID << endl;
		cout << "" << endl;
		// for loop to create the board
		cout << "  ";
		for (int x = 0; x < width; x++) {
			cout << x << " ";
		}
		cout << "" << endl;

		for (int y = 0; y < height; y++) {
			cout << y << " ";
			for (int x = 0; x < width; x++) {
				cout << BoardArray[y][x] << " ";
			}
			cout << " " << endl;
		}

	};


	void showBoardToPlayer() {
		cout << boardID << endl;
		cout << "" << endl;
		// for loop to create the board
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				if (BoardArray[y][x] == "S") {
					cout << "0" << " ";
				}
				else {
					cout << BoardArray[y][x] << " ";
				}
			}
			cout << " " << endl;
		}

	};


	bool AddBoat(SpaceShip ship, int xStart, int yStart, direction direction) {
		int shipWidth = ship.width;
		int shipHeight = ship.height;

		if (direction == vertical) {
			shipWidth = ship.height;
			shipHeight = ship.width;

		}
		if (xStart < 0) {
			cout << "A" << endl;
			return false;

		}


		if (yStart < 0) {
			cout << "b" << endl;
			return false;
		}

		if (xStart + shipWidth > width) {
			cout << "c" << endl;
			return false;
		}


		if (yStart + shipHeight > height) {
			cout << "d" << endl;
			return false;
		}


		for (int x = xStart; x < xStart + shipWidth; x++) {
			for (int y = yStart; y < yStart + shipHeight; y++) {
				if (BoardArray[y][x] == "S") {
					return false;
				}

			}

		}

		for (int x = xStart; x < xStart + shipWidth; x++) {
			for (int y = yStart; y < yStart + shipHeight; y++) {
				BoardArray[y][x] = "S";
			}
		}
		return true;
	}


	bool CheckWin() {

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (BoardArray[y][x] == "S") {
					return false;
				}
			}

		}
		return true;
	}


	void Attack(int x, int y) {

		string  tile = BoardArray[y][x];
		if (tile == "S") {
			BoardArray[y][x] = "H";
		}
		else {
			BoardArray[y][x] = "M";
		}

	}

};


Board::Board(string ID, const int x, const int y) {
	boardID = ID;
	width = x;
	height = y;
	BoardArray = new string*[y];
	for (int column = 0; column < height; column++) {
		BoardArray[column] = new string[x];
		for (int row = 0; row < width; row++) {
			BoardArray[column][row] = "0";
		}
	}

}


class GameRunner {

public:
	SpaceShip *ShipArray[4];
	Board *BoardArray[2];
	GameRunner();

	void PlayerPlacementLoop(Board board) {

		cout << "Battleships  " << endl;
		cout << " " << endl;

		board.showBoard();

		cout << " " << endl;

		GameRunner inter = GameRunner();
		SpaceShip ship = *inter.ShipArray[0];

		for (int i = 0; i < 4; i++) {
			cout << "  " << endl;
			GameRunner inter = GameRunner();	//Inter : Inter is used to run the game.
			SpaceShip ship = *inter.ShipArray[i];
			int startx, starty, direction;
			bool hasAdded;
			cout << "Ship placement layout: X Y Direction" << endl;
			cout << "Direction has to be a number. 1 = horizontal & 0 = Vertical" << endl;
			cout << "Where would you like to ship place " << i << "?" << endl;
			cout << "  " << endl;
			ship.showSpaceShip();

			cin >> startx >> starty >> direction;


			if (direction == 0) {
				hasAdded = board.AddBoat(ship, startx, starty, vertical);
			}
			else {
				hasAdded = board.AddBoat(ship, startx, starty, horizontal);
			}

			system("cls");

			if (!hasAdded)		//If hasAdded is not true then it peform a loop to ask about the previous ship. Makes it more robust. 
			{
				cout << "Invalid Placement" << endl;	// i Variable goes - 1 so that you can go to the previous ship. 
				i -= 1;
			}

			else
			{
				// HasAdded used to know if the boat has been successfully placed. if successful = 1 = good placement, 0 = invalid placement.
				cout << "Boat has been placed sucessfully" << endl;

			}
			board.showBoard();
		}
	}

	void PlayerPlacementSwitch() {

		for (int i = 0; i < 2; i++) {			// List of two players board. i equals 0 and less than 2 as there are only two boards.
			cout << "  " << endl;
			Board board = *BoardArray[i];
			PlayerPlacementLoop(board);
			system("cls");
		};
	}

	void AttackLoop() {
		Board board1 = *BoardArray[0];
		Board board2 = *BoardArray[1];

		while (!board1.CheckWin() || !board2.CheckWin()) {

			cout << "Player 1's Board" << endl;
			board1.showBoard();		// Your own board.
			cout << " " << endl;

			cout << "Enemies Board" << endl;
			board2.showBoardToPlayer();		// Other players board.

			int x, y;

			cin >> x >> y;

			board2.Attack(x, y);

			board2.showBoardToPlayer();

			system("cls");

			cout << "Player 2's Board" << endl;
			board2.showBoard();		// Your own board.
			cout << " " << endl;

			cout << "Enemies Board" << endl;
			board1.showBoardToPlayer();		// Other players board.

			cin >> x >> y;

			board1.Attack(x, y);

			board1.showBoardToPlayer();

			system("cls");
		}
		if (board1.CheckWin()) {
			cout << "Congratulations" << board1.boardID;
		}
		else {
			cout << "Congratulations" << board2.boardID;
		}


	}


};

GameRunner::GameRunner() {
	ShipArray[0] = new SpaceShip(2, 1);
	ShipArray[1] = new SpaceShip(3, 1);
	ShipArray[2] = new SpaceShip(2, 2);
	ShipArray[3] = new SpaceShip(4, 1);

	BoardArray[0] = new Board("Player 1", 8, 8);
	BoardArray[1] = new Board("Player 2", 8, 8);

}

int main() {

	GameRunner inter = GameRunner();

	inter.PlayerPlacementSwitch();
	inter.AttackLoop();

	/*
	Board board2("Player 2", 8, 8);

	board2.AddBoat(*inter.ShipArray[0],2,2, horizontal);

	board2.showBoard();


	board2.showBoardToPlayer ();

	int x, y;
	cin >> x >> y;

	board2.Attack(x, y);

	board2.showBoardToPlayer();

	//inter.PlayerPlacementSwitch();


	cout << "Battleships  " << endl;
	cout << " " << endl;

	Board board1("Player 1", 8, 8);
	board1.showBoard();

	cout << " " << endl;

	GameRunner inter = GameRunner();
	SpaceShip ship = *inter.ShipArray[0];

	for (int i = 0; i < 4; i++) {
	cout << "  " << endl;
	GameRunner inter = GameRunner();	//Inter : Inter is used to run the game.
	SpaceShip ship = *inter.ShipArray[i];
	int startx, starty, direction;
	bool hasAdded;

	cout << "Where would you like to ship place " << i << "?" << endl;
	cout << "  " << endl;
	ship.showSpaceShip();

	cin >> startx >> starty >> direction;


	if (direction == 0) {
	hasAdded = board1.AddBoat(ship, startx, starty, vertical);
	}
	else {
	hasAdded = board1.AddBoat(ship, startx, starty, horizontal);
	}

	system("cls");

	if (!hasAdded)		//If hasAdded is not true then it peform a loop to ask about the previous ship. Makes it more robust.
	{
	cout << "Invalid Placement" << endl;	// i Variable goes - 1 so that you can go to the previous ship.
	i -= 1;
	}

	else
	{
	// HasAdded used to know if the boat has been successfully placed. if successful = 1 = good placement, 0 = invalid placement.
	cout << "Boat has been placed sucessfully" << endl;

	}
	board1.showBoard();
	}
	*/

	return 0;
}