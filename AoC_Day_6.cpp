#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int solution1 = 0;

const int GO_LEFT = 8;
const int GO_DOWN = 4;
const int GO_RIGHT = 2;
const int GO_UP = 1;

struct cell {
	char marking;
	int direction;

	cell(char c, int d) {
		marking = c;
		direction = d;
	}
};

bool walkUp(vector<vector<cell>>& grid, int x, int y);

bool markPath(vector<vector<cell>>& grid, int x, int y, int direction) {
	if (grid[y][x].marking != 'X') {
		grid[y][x].marking = 'X';
		solution1++;
	}

	if ((grid[y][x].direction & direction)) {
		return true;
	}
	else {
		grid[y][x].direction |= direction;
		return false;
	}
}

bool walkLeft(vector<vector<cell>>& grid, int x, int y) {
	while (x > 0 && grid[y][x - 1].marking != '#') {
		if (markPath(grid, x, y, GO_LEFT)) {
			return true;
		}
		x--;
	}

	if (x > 0 && grid[y][x - 1].marking == '#') {
		if (walkUp(grid, x, y)) {
			return true;
		}
	}
	markPath(grid, x, y, 0);

	return false;
}

bool walkDown(vector<vector<cell>>& grid, int x, int y) {
	while (y < grid.size() - 1 && grid[y + 1][x].marking != '#') {
		if (markPath(grid, x, y, GO_DOWN)) {
			return true;
		}
		y++;
	}

	if (y < grid.size() - 1 && grid[y + 1][x].marking == '#') {
		if (walkLeft(grid, x, y)) {
			return true;
		}
	}
	markPath(grid, x, y, 0);

	return false;
}

bool walkRight(vector<vector<cell>>& grid, int x, int y) {
	while (x < grid[y].size() - 1 && grid[y][x + 1].marking != '#') {
		if (markPath(grid, x, y, GO_RIGHT)) {
			return true;
		}
		x++;
	}

	if (x < grid[y].size() - 1 && grid[y][x + 1].marking == '#') {
		if (walkDown(grid, x, y)) {
			return true;
		}
	}
	markPath(grid, x, y, 0);

	return false;
}

bool walkUp(vector<vector<cell>>& grid, int x, int y) {
	while (y > 0 && grid[y - 1][x].marking != '#') {
		if (markPath(grid, x, y, GO_UP)) {
			return true;
		}
		y--;
	}

	if (y > 0 && grid[y - 1][x].marking == '#') {
		if (walkRight(grid, x, y)) {
			return true;
		}
	}
	markPath(grid, x, y, 0);

	return false;
}

bool walkGuard(vector<vector<cell>> grid, int x, int y) {
	if (grid[y - 1][x].marking == '#') {
		return walkRight(grid, x, y);
	}
	else {
		return walkUp(grid, x, y);
	}
}

int main()
{
	ifstream inputFile("input2.txt");
	string input;
	vector<vector<cell>> grid;

	int yPositionGuard = 0;
	int xPositionGuard = 0;

	while (inputFile >> input) {
		vector<cell> cellRow;
		for (char c : input) {
			cell cellInput(c, 0);
			cellRow.push_back(cellInput);
		}

		if (input.find("^") != string::npos) {
			xPositionGuard = input.find("^");
			yPositionGuard = grid.size();
		}
		grid.push_back(cellRow);
	}

	walkGuard(grid, xPositionGuard, yPositionGuard);
	cout << solution1 << endl;

	int solution2 = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[j][i].marking != '^' && grid[j][i].marking != '#') {
				grid[j][i].marking = '#';
				if (walkGuard(grid, xPositionGuard, yPositionGuard)) {
					solution2++;
				}
				grid[j][i].marking = '.';
			}
		}
	}

	cout << solution2 << endl;
}