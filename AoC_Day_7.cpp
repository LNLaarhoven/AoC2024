#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

bool isSolveableWithAddingNext(vector<long long> values, long long expressionResult, long long currentResult);
bool isSolveableWithMultiplicationNext(vector<long long> values, long long expressionResult, long long currentResult);
bool isSolveableWithConcatenateNext(vector<long long> values, long long expressionResult, long long currentResult);

vector<string> split(const string& s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		if (item.empty())
			continue;
		result.push_back(item);
	}

	return result;
}

vector<long long> getExpressionValues(string input) {
	vector<string> splitInput = split(input, ' ');
	vector<long long> expressionValues;
	for (int i = 0; i < splitInput.size(); i++) {
		expressionValues.push_back(stoll(splitInput[i]));
	}

	return expressionValues;
}

bool isSolveableWithAddingNext(vector<long long> values, long long expressionResult, long long currentResult) {
	if (currentResult > expressionResult) {
		return false;
	}
	
	if (values.size() == 1) {
		return (currentResult + values[0]) == expressionResult;
	}

	currentResult += values[0];
	values.erase(values.begin());

	return isSolveableWithAddingNext(values, expressionResult, currentResult) ||
		isSolveableWithMultiplicationNext(values, expressionResult, currentResult) ||
		isSolveableWithConcatenateNext(values, expressionResult, currentResult);
}

bool isSolveableWithMultiplicationNext(vector<long long> values, long long expressionResult, long long currentResult) {
	if (currentResult > expressionResult) {
		return false;
	}
	
	if (values.size() == 1) {
		return (currentResult * values[0]) == expressionResult;
	}

	currentResult *= values[0];
	values.erase(values.begin());

	return isSolveableWithAddingNext(values, expressionResult, currentResult) || 
		isSolveableWithMultiplicationNext(values, expressionResult, currentResult) ||
		isSolveableWithConcatenateNext(values, expressionResult, currentResult);
}

bool isSolveableWithConcatenateNext(vector<long long> values, long long expressionResult, long long currentResult) {
	if (currentResult > expressionResult) {
		return false;
	}

	currentResult = stoll(to_string(currentResult) + to_string(values[0]));

	if (values.size() == 1) {
		return currentResult == expressionResult;
	}

	values.erase(values.begin());

	return isSolveableWithAddingNext(values, expressionResult, currentResult) ||
		isSolveableWithMultiplicationNext(values, expressionResult, currentResult) ||
		isSolveableWithConcatenateNext(values, expressionResult, currentResult);
}

bool isSolveableExpression(vector<long long> values, long long expressionResult) {
	if (values[0] > expressionResult) {
		return false;
	}

	return isSolveableWithAddingNext(values, expressionResult, 0) || isSolveableWithMultiplicationNext(values, expressionResult, 1) || isSolveableWithConcatenateNext(values, expressionResult, 0);
}


int main()
{
	long long solution1 = 0;
	ifstream inputFile("input2.txt");
	string calibration;

	while (getline(inputFile, calibration)) {
		vector<string> input = split(calibration, ':');
		long long expressionResult = stoll(input[0]);
		vector<long long> expressionValues = getExpressionValues(input[1]);
		
		if (isSolveableExpression(expressionValues, expressionResult)) {
			solution1 += expressionResult;
		}
	}

	cout << solution1 << endl;
}