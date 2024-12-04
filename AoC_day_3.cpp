#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    regex regularExpression(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don\'t\(\))");
    smatch matchedString;

    string input;
    ifstream inputFile("input2.txt");

    int sumOfMultiplications = 0;
    bool isMultiplicationEnabled = true;

    while (inputFile >> input) {
        string::const_iterator searchStart(input.cbegin());
        
        while (regex_search(searchStart, input.cend(), matchedString, regularExpression))
        {
            string result = matchedString[0];
            if (result.rfind("mul", 0) == 0 && isMultiplicationEnabled) {
                int a = stoi(matchedString[1]);
                int b = stoi(matchedString[2]);

                sumOfMultiplications += (a * b);
            }
            else if (result.rfind("don", 0) == 0) {
                isMultiplicationEnabled = false;
            }
            else if (result.rfind("do", 0) == 0) {
                isMultiplicationEnabled = true;
            }

            searchStart = matchedString.suffix().first;
        }
    }

    cout << sumOfMultiplications << endl;
}