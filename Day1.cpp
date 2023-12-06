// AOC.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <regex>
#include <unordered_map>
#include "Test.h"

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"


class AdventOfCodeDay1 {
private:
	

#pragma region String test cases

	void testNoDigit() {
		std::string text = "bgasbdgldbglabglb";
		std::string actual = findfirstlastdigit(text);
		assertEqual(actual, "00", "Test string - no digit");
	}

	void testFirstLastDigit() {
		std::string text = "2bgsbdgldbglabgl3";
		std::string actual = findfirstlastdigit(text);
		assertEqual(actual, "23", "Test string - no digit");
	}

	void testFirstOnly() {
		std::string text = "8gasdgldbglabglb";
		std::string actual = findfirstlastdigit(text);
		assertEqual(actual, "88", "Test string - FirstOnly");
	}

	void testLastOnly() {
		std::string text = "bgasbdgldbglabgl9";
		std::string actual = findfirstlastdigit(text);
		assertEqual(actual, "99", "Test string - last only");
	}

	void testOnlyDigit() {
		std::string text = "142946126421538213";
		std::string actual = findfirstlastdigit(text);
		assertEqual(actual, "13", "Test string - onlydigit");
	}

	void testDigitInside() {
		std::string text = "asfsafa1a233bfl231asfbv2";
		std::string actual = findfirstlastdigit(text);
		assertEqual(actual, "12", "Test string - digit inside");
	}

	void testTextDigit() {
		std::string text = "oneightwonethree";
		replaceTextDigit(text);
		std::string actual = findfirstlastdigit(text);
		assertEqual(actual, "13", "Test string - digit inside");
	}

#pragma endregion

#pragma region int test cases

	void testIntNoDigit() {
		std::string text = "bgasbdgldbglabglb";
		std::string actual = findfirstlastdigit(text);
		assertEqualInt(std::stoi(actual), 0, "Test int - no digit");
	}

	void testIntFirstLastDigit() {
		std::string text = "2bgsbdgldbglabgl3";
		std::string actual = findfirstlastdigit(text);
		assertEqualInt(std::stoi(actual), 23, "Test int - no digit");
	}

	void testIntFirstOnly() {
		std::string text = "8gas8dgldbglabglb";
		std::string actual = findfirstlastdigit(text);
		assertEqualInt(std::stoi(actual), 88, "Test int - FirstOnly");
	}

	void testIntLastOnly() {
		std::string text = "bgasbdgldbglabgl9";
		std::string actual = findfirstlastdigit(text);
		assertEqualInt(std::stoi(actual), 99, "Test int - last only");
	}

	void testIntOnlyDigit() {
		std::string text = "142946126421538213";
		std::string actual = findfirstlastdigit(text);
		assertEqualInt(std::stoi(actual), 13, "Test int - onlydigit");
	}

	void testIntDigitInside() {
		std::string text = "asfsafa1a233bfl231asfbv2";
		std::string actual = findfirstlastdigit(text);
		assertEqualInt(std::stoi(actual), 12, "Test int - digit inside");
	}

#pragma endregion

	std::unordered_map<std::string, std::string> textDigit = {
		{ "one", "o1e" },
		{ "two", "t2o" },
		{ "three", "t3e" },
		{ "four", "f4r" },
		{ "five", "f5e" },
		{ "six", "s6x" },
		{ "seven", "s7n" },
		{ "eight", "e8t" },
		{ "nine", "n9e" }
	};

	void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
	}

	void replaceTextDigit(std::string& stringa) {
		for (auto x : textDigit) {
			int index = stringa.find(x.first);
			if (index == std::string::npos)
				continue;
			replaceAll(stringa, x.first, x.second);
		}
	}


	std::string findfirstlastdigit(std::string& stringa) {
		std::string start("0"), end("0");
		for (auto c : stringa) {
			if (isdigit(c)) {
				start = c;
				break;
			}
		}

		std::reverse(stringa.begin(), stringa.end());
		for (auto c : stringa) {
			if (isdigit(c)) {
				end = c;
				break;
			}
		}

		return start + end;
	}

public:
	void unitTest() {
		//string test
		testDigitInside();
		testFirstLastDigit();
		testFirstOnly();
		testLastOnly();
		testNoDigit();
		testOnlyDigit();
		testTextDigit();

		//int test
		testIntDigitInside();
		testIntFirstLastDigit();
		testIntFirstOnly();
		testIntLastOnly();
		testIntNoDigit();
		testIntOnlyDigit();
	}


	int day1() {
		std::ifstream day1File("Day1.txt");
		std::string line;
		int sum = 0;
		if (day1File.is_open())
			while (std::getline(day1File, line)) {
				replaceTextDigit(line);
				sum += std::stoi(findfirstlastdigit(line));
			}
		return sum;
	}
};
