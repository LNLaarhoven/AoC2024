#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

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

unordered_map<int, vector<int>> getBlockedByNumbers(ifstream& fileStream) {
	string inputLine;

	unordered_map<int, vector<int>> blockedByNumbers;

	while (getline(fileStream, inputLine, '\n')) {

		if (inputLine.empty()) {
			return blockedByNumbers;
		}

		vector<int> rule = split(inputLine, '|');
		blockedByNumbers[rule[1]].push_back(rule[0]);
	}
}

bool isValidUpdate(vector<int> update, unordered_map<int, vector<int>>& rules) {
	
	for (int i = 0; i < update.size(); i++) {
		for (int j = i + 1; j < update.size(); j++) {
			if (find(rules[update[i]].begin(), rules[update[i]].end(), update[j]) != rules[update[i]].end()) {
				return false;
			}
		}
	}

	return true;
}

void swapNumbers(vector<int>& update, int i, int j) {
	int temp = update[i];
	update[i] = update[j];
	update[j] = temp;
}

void bringPageForward(vector<int>& update, int i, int j) {
	for (int k = j; k > i; k--) {
		swapNumbers(update, k, k - 1);
	}
}

void findCorrectPageForLocation(vector<int>& update, unordered_map<int, vector<int>>& rules, int i) {
	for (int j = i + 1; j < update.size(); j++) {
		while (find(rules[update[i]].begin(), rules[update[i]].end(), update[j]) != rules[update[i]].end()) {
			bringPageForward(update, i, j);
		}
	}
}

vector<int> orderBrokenUpdate(vector<int> update, unordered_map<int, vector<int>>& rules) {
	for (int i = 0; i < update.size(); i++) {
		findCorrectPageForLocation(update, rules, i);
	}

	return update;
}

int main()
{
	ifstream inputFile("input2.txt");
	string update;

	unordered_map<int, vector<int>> rules = getBlockedByNumbers(inputFile);

	int solution1 = 0;
	int solution2 = 0;

	while (inputFile >> update) {
		vector<int> pages = split(update, ',');

		if (isValidUpdate(pages, rules)) {
			solution1 += pages[pages.size() / 2];
		}
		else {
			solution2 += orderBrokenUpdate(pages, rules)[pages.size() / 2];
		}
	}

	cout << solution1 << endl;
	cout << solution2 << endl;
}