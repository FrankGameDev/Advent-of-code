#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <numeric>
#include <unordered_map>
#include "Day4.h"
#include "../Utils/Utility.h"


using namespace std;
class Day4 {
private:
	int analyzeGamesPart1(const vector<string>& lines) {
		int totalPoints = 0;

		for (const string& line : lines) {
			istringstream iss(line);
			string gameAndWinningNumber, ourNumbersStr, winningNumbers, tmp;

			getline(iss, gameAndWinningNumber, '|');
			getline(iss, ourNumbersStr);
			vector<string> ourNumber = split(ourNumbersStr, ' ');

			istringstream iss2(gameAndWinningNumber);
			getline(iss2, tmp, ':');
			getline(iss2, winningNumbers);

			totalPoints += (1 << (checkWins(winningNumbers, ourNumber) - 1));
		}

		return totalPoints;
	}

	int checkWins(const string& winningNumbersStr, const vector<string>& ourNumbers) {
		int point = 0;
		istringstream winningNumbersStream(winningNumbersStr);
		string wnum;

		while (winningNumbersStream >> wnum) {
			trim(wnum);
			if (!wnum.empty() && find(ourNumbers.begin(), ourNumbers.end(), wnum) != ourNumbers.end()) {
				point += 1;
			}
		}

		return point;
	}


	int analyzeScratchcards(const vector<string>& lines) {
		unordered_map<int, int> scratchPoints;
		for (string line : lines) {
			computeScratchcardsCount(scratchPoints, line);
		}
		vector<int> scratchPointValues;
		for (auto pair : scratchPoints) {
			scratchPointValues.emplace_back(pair.second);
		}

		return reduce(scratchPointValues.begin(), scratchPointValues.end());
	}

	void computeScratchcardsCount(unordered_map<int, int>& scratchPoints, string& line) {
		istringstream iss(line);
		string gameAndWinningNumber, ourNumbersStr, winningNumbers, tmp;

		getline(iss, gameAndWinningNumber, '|');
		getline(iss, ourNumbersStr);
		vector<string> ourNumber = split(ourNumbersStr, ' ');

		istringstream iss2(gameAndWinningNumber);
		getline(iss2, tmp, ':');
		getline(iss2, winningNumbers);

		regex pattern("\\b(\\d+)\\b");
		smatch match;
		int scratchNum;
		if (regex_search(tmp, match, pattern)) {
			std::string numberStr = match[1].str();
			scratchNum = std::stoi(numberStr);
		}
		else 
			return;
		

		if (scratchPoints.find(scratchNum) == scratchPoints.end())
			scratchPoints.emplace(scratchNum, 1);

		int point = checkWins(winningNumbers, ourNumber);

		for (int i = 1; i <= point; i++) {
			if (scratchPoints.find(scratchNum + i) == scratchPoints.end())
				scratchPoints.emplace(scratchNum + i, 1);
			else
				scratchPoints[scratchNum + i] += scratchPoints[scratchNum] + 1;
		}
	}

public:
	void part1() {
		vector<string> lines = readFile("Day4.txt");
		int result = analyzeGamesPart1(lines);
		cout << result << endl;
	}

	void part2() {
		vector<string> lines = readFile("Day4.txt");
		int result = analyzeScratchcards(lines);
		cout << result << endl;
	}
};



int main() {
	Day4().part2();
}