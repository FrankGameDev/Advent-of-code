#include "Day2.h"
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <regex>
#include <unordered_map>
#include "../Utils/Test.h"
#include "../Utils/Utility.h"


using namespace std;

class CubeBag {
	int red, blue, green;
	int maxRedCubes = 12, maxGreenCubes = 13, maxBlueCubes = 14;

public:
	CubeBag() : red(0), blue(0), green(0) {}

	void putRed(int n) {
		red = max(red, n);
	}

	void putGreen(int n) {
		green = max(green, n);
	}

	void putBlue(int n) {
		blue = max(blue, n);
	}

	bool checkPossibleGame() const {
		return red <= maxRedCubes && blue <= maxBlueCubes && green <= maxGreenCubes;
	}

	int getPowerOfCubes() const {
		return red * blue * green;
	}
};

class Day2 {

private:
	pair<int, CubeBag> countCubesPerGame(string& line) {
		pair<int, CubeBag> result;
		vector<string> gameNCubes = split(line, ':');
		int game = stoi(split(gameNCubes[0], ' ')[1]);
		result.first = game;
		string extractions = gameNCubes[1];
		trim(extractions);
		vector<string> round = split(extractions, ';');
		CubeBag cubeBag;
		for (string r : round)
		{
			vector<string> cubes = split(r, ',');
			for (string c : cubes)
				countCubeOccuranceOfColor(c, cubeBag);
		}
		result.second = cubeBag;
		return result;
	}

	/// <summary>
	/// Read a string like this "number color" and add the correct number of cubes to the cube bag
	/// </summary>
	/// <param name="round"></param>
	/// <param name="color"></param>
	/// <returns></returns>
	void countCubeOccuranceOfColor(string& cube, CubeBag& color) {
		trim(cube);
		vector<string> splitted = split(cube, ' ');
		if (splitted[1] == "blue")
			color.putBlue(stoi(splitted[0]));
		if (splitted[1] == "green")
			color.putGreen(stoi(splitted[0]));
		if (splitted[1] == "red")
			color.putRed(stoi(splitted[0]));
	}


	int getSumIdWithRequestedCube(unordered_map<int, CubeBag>& cubePerGame, int& sum) {
		for (pair<int, CubeBag> x : cubePerGame) {
			if (x.second.checkPossibleGame())
				sum += x.first;
		}
		return sum;
	}

	int getPowerAndSumOfCubes(unordered_map<int, CubeBag> cubePerGame, int& sum) {
		for (pair<int, CubeBag> x : cubePerGame) {
			sum += x.second.getPowerOfCubes();
		}
		return sum;
	}

public:
	int Part1() {
		std::ifstream file("Day2.txt");
		std::string line;
		int sum = 0;
		unordered_map<int, CubeBag> cubePerGame;
		if (file.is_open()) {
			while (getline(file, line)) {
				auto result = countCubesPerGame(line);
				cubePerGame.insert_or_assign(result.first, result.second);
			}
		}
		getSumIdWithRequestedCube(cubePerGame, sum);

		return sum;
	}

	int Part2() {
		std::ifstream file("Day2.txt");
		std::string line;
		int sum = 0;
		unordered_map<int, CubeBag> cubePerGame;
		if (file.is_open()) {
			while (getline(file, line)) {
				pair<int, CubeBag> result = countCubesPerGame(line);
				cubePerGame.insert_or_assign(result.first, result.second);
			}
		}
		getPowerAndSumOfCubes(cubePerGame, sum);

		return sum;
	}

};

int main() {
	cout << Day2().Part1() << endl;
	cout << Day2().Part2() << endl;
}