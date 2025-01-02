#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> transformSeperatedInput(vector<char>& input) {
	vector<int> result;

	bool isMemoryBlock = true;
	int id = 0;

	for (int i = 0; i < input.size(); i++) {
		int digit = input[i] - '0';
		if (isMemoryBlock) {
			for (int j = 0; j < digit; j++) {
				result.push_back(id);
			}
			id++;
		}
		else {
			for (int j = 0; j < digit; j++) {
				result.push_back(-1);
			}
		}

		isMemoryBlock = !isMemoryBlock;
	}

	return result;
}

vector<int> moveMemoryBlocks(vector<int> input) {
	int leftPointer = 0;
	int rightPointer = input.size() - 1;

	while (leftPointer < rightPointer) {
		if (input[leftPointer] != -1) {
			leftPointer++;
		}
		else {
			input[leftPointer] = input[rightPointer];
			input[rightPointer] = -1;
			leftPointer++;
			do {
				rightPointer--;
			} while (input[rightPointer] == -1);
		}
	}

	return input;
}

long long calculateResult(vector<int> input) {
	long long result = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == -1)
			break;

		result += i * input[i];
	}

	return result;
}

int main()
{
	ifstream inputFile("input.txt");
	string input;
	inputFile >> input;
	vector<char> inputSeperated(input.begin(), input.end());

	vector<int> transformedResult = transformSeperatedInput(inputSeperated);
	vector<int> movedResult = moveMemoryBlocks(transformedResult);
	
	long long result = calculateResult(movedResult);

	cout << result << endl;
}
