#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string inputPath = "input.txt";
	fstream inputFile;
	vector<string> inputData;

	inputFile.open(inputPath, ios::in);
	if (inputFile.is_open()) {
		string line;
		while (getline(inputFile, line)) {
			inputData.push_back(line);
		}
		inputFile.close();
	}

	cout << inputData[2][4];
}