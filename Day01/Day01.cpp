#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int parseCalibrationValue(string line, const string& digitString, string digits[]) {
	int firstDigitPos = line.find_first_of(digitString);
	int lastDigitPos = line.find_last_of(digitString);
	char firstDigit = line.at(firstDigitPos);
	char lastDigit = line.at(lastDigitPos);
	int writtenDigitFirstPos;
	int writtenDigitLastPos;
	for (int i = 0; i < 10; i++) {
		writtenDigitFirstPos = line.find(digits[i]);
		writtenDigitLastPos = line.rfind(digits[i]);
		if (writtenDigitFirstPos >= 0 && writtenDigitFirstPos < firstDigitPos) {
			firstDigitPos = writtenDigitFirstPos;
			firstDigit = i + '0';
		}
		if (writtenDigitLastPos >= 0 && writtenDigitLastPos > lastDigitPos) {
			lastDigitPos = writtenDigitLastPos;
			lastDigit = i + '0';
		}
	}
	
	string calibrationValue = { firstDigit, lastDigit };
	return stoi(calibrationValue);
}

int main()
{
	string digitString = "0123456789";
	string digits[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string inputPath = "input.txt";
	fstream inputFile;
	int total = 0;

	inputFile.open(inputPath, ios::in);
	if (inputFile.is_open()) {
		string line;
		while (getline(inputFile, line)) {
			total += parseCalibrationValue(line, digitString, digits);
		}
		inputFile.close();
	}
	cout << total;
}