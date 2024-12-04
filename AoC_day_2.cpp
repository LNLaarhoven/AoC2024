#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

vector<int> split(const string& s, char delim) {
	vector<int> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		if (item.empty())
			continue;
		result.push_back(stoi(item));
	}

	return result;
}

bool isReportIncreasingAndDecreasing(int a, int b, bool isIncreasing) {
	return (isIncreasing && a >= b) || (!isIncreasing && a <= b);
}

bool isDistanceBiggerThanThree(int a, int b) {
	return abs(a - b) > 3;
}

bool areLevelsSafe(int a, int b, bool isIncreasing) {
	return isReportIncreasingAndDecreasing(a, b, isIncreasing) ||
		   isDistanceBiggerThanThree(a, b);
}

bool isSafeReport(vector<int> report) {
	bool isIncreasing = true;

	for (int i = 0; i < report.size() - 1; i++) {
		if (i == 0) {
			isIncreasing = report[i] < report[i + 1];
		}

		if (areLevelsSafe(report[i], report[i + 1], isIncreasing)) {
			return false;
		}
	}

	return true;
}

bool isSafeReportWithLevelRemoved(vector<int> report, int indexToBeRemoved) {
	report.erase(report.begin() + indexToBeRemoved);
	return isSafeReport(report);
}

bool isSafeReportWithALevelRemoved(vector<int> report) {
	for (int i = 0; i < report.size(); i++) {
		if (isSafeReportWithLevelRemoved(report, i)) {
			return true;
		}
	}
	return false;
}

int main()
{
	ifstream inputFile("input.txt");
	vector<int> report;
	string input;

	int safeReports = 0;

	while (getline(inputFile, input))
	{
		vector<int> report = split(input, ' ');

		if (isSafeReport(report) || isSafeReportWithALevelRemoved(report)) {
			safeReports++;
		}
	}
	
	cout << safeReports << endl;
}