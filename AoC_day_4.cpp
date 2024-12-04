#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<char> word({ 'X', 'M', 'A', 'S' });

bool findWordTopLeft(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (xStart < 3 || yStart < 3)
		return false;
	else
		return wordSearch[yStart - 1][xStart - 1] == 'M' &&
			   wordSearch[yStart - 2][xStart - 2] == 'A' &&
		       wordSearch[yStart - 3][xStart - 3] == 'S';
}

bool findWordTop(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (yStart < 3)
		return false;
	else
		return wordSearch[yStart - 1][xStart] == 'M' &&
			   wordSearch[yStart - 2][xStart] == 'A' &&
			   wordSearch[yStart - 3][xStart] == 'S';
}

bool findWordTopRight(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (xStart > (wordSearch[0].size() - 4) || yStart < 3)
		return false;
	else
		return wordSearch[yStart - 1][xStart + 1] == 'M' &&
			   wordSearch[yStart - 2][xStart + 2] == 'A' &&
			   wordSearch[yStart - 3][xStart + 3] == 'S';
}

bool findWordLeft(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (xStart < 3)
		return false;
	else
		return wordSearch[yStart][xStart - 1] == 'M' &&
			   wordSearch[yStart][xStart - 2] == 'A' &&
			   wordSearch[yStart][xStart - 3] == 'S';
}

bool findWordRight(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (xStart > (wordSearch[0].size() - 4))
		return false;
	else
		return wordSearch[yStart][xStart + 1] == 'M' &&
			   wordSearch[yStart][xStart + 2] == 'A' &&
			   wordSearch[yStart][xStart + 3] == 'S';
}

bool findWordBottomLeft(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (xStart < 3 || yStart > (wordSearch.size() - 4))
		return false;
	else
		return wordSearch[yStart + 1][xStart - 1] == 'M' &&
			   wordSearch[yStart + 2][xStart - 2] == 'A' &&
			   wordSearch[yStart + 3][xStart - 3] == 'S';
}

bool findWordBottom(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (yStart > (wordSearch.size() - 4))
		return false;
	else
		return wordSearch[yStart + 1][xStart] == 'M' &&
			   wordSearch[yStart + 2][xStart] == 'A' &&
			   wordSearch[yStart + 3][xStart] == 'S';
}

bool findWordBottomRight(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	if (xStart > (wordSearch[0].size() - 4) || yStart > (wordSearch.size() - 4))
		return false;
	else
		return wordSearch[yStart + 1][xStart + 1] == 'M' &&
			   wordSearch[yStart + 2][xStart + 2] == 'A' &&
			   wordSearch[yStart + 3][xStart + 3] == 'S';
}

int solvePart1(vector<vector<char>>& wordSearch) {
	int solution = 0;

	for (int i = 0; i < wordSearch.size(); i++) {
		for (int j = 0; j < wordSearch[i].size(); j++) {
			if (wordSearch[i][j] == 'X') {
				solution +=
					findWordTopLeft(j, i, wordSearch) +
					findWordTop(j, i, wordSearch) +
					findWordTopRight(j, i, wordSearch) +
					findWordLeft(j, i, wordSearch) +
					findWordRight(j, i, wordSearch) +
					findWordBottomLeft(j, i, wordSearch) +
					findWordBottom(j, i, wordSearch) +
					findWordBottomRight(j, i, wordSearch);
			}
		}
	}

	return solution;
}

bool findMASLeft(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	return wordSearch[yStart + 1][xStart + 1] == 'M' &&
		   wordSearch[yStart - 1][xStart + 1] == 'M' &&
		   wordSearch[yStart + 1][xStart - 1] == 'S' &&
		   wordSearch[yStart - 1][xStart - 1] == 'S';
}

bool findMASRight(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	return wordSearch[yStart + 1][xStart + 1] == 'S' &&
		   wordSearch[yStart - 1][xStart + 1] == 'S' &&
		   wordSearch[yStart + 1][xStart - 1] == 'M' &&
		   wordSearch[yStart - 1][xStart - 1] == 'M';
}

bool findMASTop(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	return wordSearch[yStart - 1][xStart - 1] == 'S' &&
		wordSearch[yStart - 1][xStart + 1] == 'S' &&
		wordSearch[yStart + 1][xStart - 1] == 'M' &&
		wordSearch[yStart + 1][xStart + 1] == 'M';
}

bool findMASBottom(int xStart, int yStart, vector<vector<char>>& wordSearch) {
	return wordSearch[yStart - 1][xStart - 1] == 'M' &&
		wordSearch[yStart - 1][xStart + 1] == 'M' &&
		wordSearch[yStart + 1][xStart - 1] == 'S' &&
		wordSearch[yStart + 1][xStart + 1] == 'S';
}

int solvePart2(vector<vector<char>> wordSearch) {
	int solution = 0;

	for (int i = 1; i < wordSearch.size() - 1; i++) {
		for (int j = 1; j < wordSearch[i].size() - 1; j++) {
			if (wordSearch[i][j] == 'A') {
				solution += 
					findMASLeft(j, i, wordSearch) ||
					findMASRight(j, i, wordSearch) ||
					findMASTop(j, i, wordSearch) ||
					findMASBottom(j, i, wordSearch);
			}
		}
	}

	return solution;
}

int main()
{
	ifstream inputFile("input2.txt");
	string input;
	vector<vector<char>> wordSearch;
	int solution = 0;
	
	while (inputFile >> input) {
		vector<char> row(input.begin(), input.end());
		wordSearch.push_back(row);
	}

	cout << solvePart1(wordSearch) << endl;
	cout << solvePart2(wordSearch) << endl;
}