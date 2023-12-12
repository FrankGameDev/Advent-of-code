#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <regex>
#include <numeric>
#include <unordered_map>
#include "../Utils/Utility.h"

using namespace std;

class Day3 {

private:
	vector<int> part1Solution(vector<string>& lines) {
		vector<int> numFound;
		unordered_map<int, vector<int>> visited;
		for (int i = 0; i < lines.size(); i++) { // Rows
			for (int j = 0; j < lines[i].size(); j++) { //Columns
				if (!checkIfSymbol(lines[i][j]))
					continue;

				vector<int> result = findNumbersFromSymbol(lines, i, j, visited);
				numFound.insert(numFound.end(), result.begin(), result.end());
			}
		}

		return numFound;
	}


	vector<int> part2Solution(vector<string>& lines) {
		vector<int> numFound;
		unordered_map<int, vector<int>> visited;
		for (int i = 0; i < lines.size(); i++) { // Rows
			for (int j = 0; j < lines[i].size(); j++) { //Columns
				if (!checkIfGear(lines[i][j]))
					continue;

				vector<int> result = findNumbersFromSymbol(lines, i, j, visited);
				if (result.size() != 2)
					continue;

				int power = result[0] * result[1];
				numFound.emplace_back(power);
			}
		}

		return numFound;
	}

	


	// Utils

	bool checkIfSymbol(char& c) {
		return c != '.' && !isdigit(c);
	}

	bool checkIfGear(char& c) {
		return c == '*';
	}

	vector<int> findNumbersFromSymbol(const vector<string>& lines, int rowIndex, int columnIndex, unordered_map<int, vector<int>>& visited) {
		vector<string> numString;
		vector<int> result;

		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex - 1], rowIndex - 1, columnIndex, visited));
		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex + 1], rowIndex + 1, columnIndex, visited));
		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex], rowIndex, columnIndex + 1, visited));
		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex], rowIndex, columnIndex - 1, visited));
		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex - 1], rowIndex - 1, columnIndex - 1, visited));
		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex - 1], rowIndex - 1, columnIndex + 1, visited));
		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex + 1], rowIndex + 1, columnIndex - 1, visited));
		numString.push_back(parseNumberFromStartingPoint(lines[rowIndex + 1], rowIndex + 1, columnIndex + 1, visited));


		for (string s : numString) {
			if (s.empty() || find_if(s.begin(), s.end(), [&](unsigned char c) {return isdigit(c); }) == s.end())
				continue;

			result.push_back(stoi(s));
		}

		return result;
	}

	string parseNumberFromStartingPoint(const string line, int row, int col, unordered_map<int, vector<int>>& visited) {
		unordered_map<int, string> indexes;

		bool indexVisited = find_if(visited.begin(), visited.end(), [&](const auto& entry) {
			return entry.first == row &&
				find(entry.second.begin(), entry.second.end(), col) != entry.second.end();
			}) != visited.end();

			// Check if the row and the column has been visited already
			if (indexVisited)
				return "";

			return parseNumberFromStartingPoint(line, col, indexes, visited, row);
	}

	string parseNumberFromStartingPoint(const string line, int col, unordered_map<int, string>& indexes, unordered_map<int, vector<int>>& visited, int visitedKey) {
		if (indexes.find(col) != indexes.end())
			return "";
		if (!isdigit(line[col]))
			return "";
		if (col == 0 || col == line.length() - 1)
			return string(1, line[col]);

		indexes.insert_or_assign(col, string(1, line[col]));
		if (visited.find(visitedKey) == visited.end()) {
			vector<int> tmp;
			tmp.push_back(col);
			visited.emplace(visitedKey, tmp);
		}
		else
			visited[visitedKey].push_back(col);
		return parseNumberFromStartingPoint(line, col - 1, indexes, visited, visitedKey) + line[col] + parseNumberFromStartingPoint(line, col + 1, indexes, visited, visitedKey);
	}


public:
	int part1() {
		vector<string> lines = readFile("Day3.txt");
		vector<int> numbers = part1Solution(lines);
		return reduce(numbers.begin(), numbers.end());
	}

	int part2() {
		vector<string> lines = readFile("Day3.txt");
		vector<int> numbers = part2Solution(lines);
		return reduce(numbers.begin(), numbers.end());
	}
};
