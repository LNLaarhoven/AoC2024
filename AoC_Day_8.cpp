#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

struct Antenna {
	int positionX;
	int positionY;

	Antenna(int positionX, int positionY)
		: positionX(positionX), positionY(positionY)
	{
	}
};

int solution1 = 0;

unordered_map<char, vector<Antenna>> getAntennaPerFrequency(vector<vector<char>>& inputGrid) {
	unordered_map<char, vector<Antenna>> antennaPerFrequency;

	for (int i = 0; i < inputGrid.size(); i++) {
		for (int j = 0; j < inputGrid[i].size(); j++) {
			if (inputGrid[j][i] != '.') 
				antennaPerFrequency[inputGrid[j][i]].push_back(Antenna(i, j));
		}
	}

	return antennaPerFrequency;
}

bool isOnGrid(int size, int position) {
	return position >= 0 && position < size;
}

bool isPositionOnGrid(int size, int x, int y) {
	return isOnGrid(size, y) && isOnGrid(size, x);
}

void MarkAntinodeGrid(vector<vector<char>>& antinodeGrid, int x, int y) {
	if (antinodeGrid[y][x] == '.') {
		antinodeGrid[y][x] = '#';
		solution1++;
	}
}

void CalculateAntinodes(vector<vector<char>>& antinodeGrid, Antenna a, Antenna b) {

	int deltaX = a.positionX - b.positionX;
	int deltaY = a.positionY - b.positionY;
	const int greatestCommonDivisor = gcd(deltaX, deltaY);
	
	int xSlope = deltaX / greatestCommonDivisor;
	int ySlope = deltaY / greatestCommonDivisor;

	int x = a.positionX;
	int y = a.positionY;

	while (isPositionOnGrid(antinodeGrid.size(), x, y)) {
		MarkAntinodeGrid(antinodeGrid, x, y);
		x += xSlope;
		y += ySlope;
	}

	x = a.positionX - xSlope;
	y = a.positionY - ySlope;

	while (isPositionOnGrid(antinodeGrid.size(), x, y)) {
		MarkAntinodeGrid(antinodeGrid, x, y);
		x -= xSlope;
		y -= ySlope;
	}
}

vector<vector<char>> getAntinodeGrid(vector<vector<char>> inputGrid) {
	unordered_map<char, vector<Antenna>> antennasPerFrequency = getAntennaPerFrequency(inputGrid);
	vector<vector<char>> antinodeGrid(inputGrid.size(), vector<char>(inputGrid[0].size(), '.'));

	for (auto frequency : antennasPerFrequency) {

		for (int i = 0; i < frequency.second.size() - 1; i++) {
			for (int j = i + 1; j < frequency.second.size(); j++) {
				Antenna a = frequency.second[i];
				Antenna b = frequency.second[j];
				if (a.positionX <= b.positionX) {
					CalculateAntinodes(antinodeGrid, a, b);
				}
				else {
					CalculateAntinodes(antinodeGrid, b, a);
				}
			}
		}
	}

	return antinodeGrid;
}

int main()
{
	ifstream inputFile("input.txt");
	string input;
	vector<vector<char>> inputGrid;
	vector<vector<char>> antinodeGrid;

	while (inputFile >> input) {
		vector<char> row(input.begin(), input.end());
		inputGrid.push_back(row);
	}

	antinodeGrid = getAntinodeGrid(inputGrid);

	for (vector<char> row : antinodeGrid) {
		string s(row.begin(), row.end());
		cout << s << endl;
	}

	cout << solution1 << endl;
}