#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Game {
	int id;
	vector<vector<int>> sets;
	bool possible;
	vector<int> maxCubes;
};

vector<string> split(const string& text, const string& separator) {
	vector<string> splitText;
	int startPos = 0;
	int nextPos = text.find(separator, startPos);
	while (nextPos >= 0) {
		if (startPos == nextPos) {
			startPos = nextPos + 1;
			nextPos = text.find(separator, startPos);
		}
		else {
			splitText.push_back(text.substr(startPos, nextPos - startPos));
			startPos = nextPos + 1;
			nextPos = text.find(separator, startPos);
		}
	}
	splitText.push_back(text.substr(startPos));
	return splitText;
}

Game parseLine(const string& line, const vector<string>& colors, const vector<int>& maxPossibleCubes) {
	vector<int> maxCubes = { 0, 0, 0 };

	vector<string> setStrings = split(line, ";");
	string firstString = setStrings.at(0);
	int id = stoi(firstString.substr(5, firstString.find(':') - 5));

	bool possible = true;
	vector<vector<int>> sets;
	for (string setString : setStrings) {
		vector<int> set;
		for (int i = 0; i < colors.size(); i++) {
			string color = colors.at(i);
			int pos = setString.find(color);
			if (pos > 1) {
				vector<string> spaceSplit = split(setString.substr(0, pos - 1), " ");
				int nCubes = stoi(spaceSplit.back());
				if (nCubes > maxPossibleCubes.at(i)) {
					possible = false;
				}
				if (nCubes > maxCubes.at(i)) {
					maxCubes.at(i) = nCubes;
				}
				set.push_back(nCubes);
			}
			else {
				set.push_back(0);
			}
		}
		sets.push_back(set);
	}

	return Game{ id, sets, possible, maxCubes };
}

int sumUpPossibleGames(vector<Game>& games) {
	int total = 0;
	for (Game game : games) {
		if (game.possible) {
			total += game.id;
		}
	}
	return total;
}

int getPower(Game game) {
	int power = game.maxCubes.at(0) * game.maxCubes.at(1) * game.maxCubes.at(2);
	return power;
}

int sumUpPowers(vector<Game>& games) {
	int total = 0;
	for (Game game : games) {
		total += getPower(game);
	}
	return total;
}

int main()
{
	vector<string> colors = { "red", "green", "blue" };
	vector<int> maxPossibleCubes = { 12, 13, 14 };
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

	vector<Game> games;
	for (string line : inputData) {
		games.push_back(parseLine(line, colors, maxPossibleCubes));
	}

	int totalPossible = sumUpPossibleGames(games);
	cout << "Total Possible: " << totalPossible << "\n";

	int totalPower = sumUpPowers(games);
	cout << "Total Power: " << totalPower;
}