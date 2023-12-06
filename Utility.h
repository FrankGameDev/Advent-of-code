#pragma once

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <vector>

using namespace std;

// trim from start (in place)
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}

static vector<string> split(string& s, char separator) {
	vector<string> result;
	int startIndex = 0, endIndex = 0;
	for (int i = 0; i <= s.size(); i++) {

		// If we reached the end of the word or the end of the input.
		if (s[i] == separator || i == s.size()) {
			endIndex = i;
			string temp;
			temp.append(s, startIndex, endIndex - startIndex);
			result.push_back(temp);
			startIndex = endIndex + 1;
		}
	}
	return result;

}
