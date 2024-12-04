#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cmath>

using namespace std;

int part1(list<int> leftList, list<int> rightList) {
	int distance = 0;
	while (!leftList.empty()) {
		int leftNumber = leftList.front();
		leftList.pop_front();
		int rightNumber = rightList.front();
		rightList.pop_front();

		distance += abs(leftNumber - rightNumber);
	}

	return distance;
}

int part2(list<int> leftList, list<int> rightList) {
	int distance = 0;
	while (!leftList.empty() && !rightList.empty()) {
		if (leftList.front() < rightList.front()) {
			leftList.pop_front();
		}
		else if (leftList.front() > rightList.front()) {
			rightList.pop_front();
		}
		else {
			int number = leftList.front();
			int amountOfOccurences = 0;
			while (!rightList.empty() && rightList.front() == leftList.front()) {
				amountOfOccurences++;
				rightList.pop_front();
			}
			while (!leftList.empty() && leftList.front() == number) {
				distance += number * amountOfOccurences;
				leftList.pop_front();
			}
		}
	}

	return distance;
}

int main()
{
	ifstream inputFile("input2.txt");

	int leftSide, rightSide;

	list<int> leftList;
	list<int> rightList;

	while (inputFile >> leftSide >> rightSide) {
		leftList.push_back(leftSide);
		rightList.push_back(rightSide);
	}

	int distance = 0;

	leftList.sort();
	rightList.sort();
	cout << part1(leftList, rightList) << endl;
	cout << part2(leftList, rightList) << endl;
}