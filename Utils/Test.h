#pragma once
#include <iostream>
#include <string.h>

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

using namespace std;

/// <summary>
/// Test di assert uguaglianza
/// </summary>
/// <param name="actual"></param>
/// <param name="expected"></param>
/// <param name="message"></param>
static void assertEqual(string actual, string expected, const char* message) {
	if (actual == expected) {
		cout << GREEN << "[PASS] " << RESET << message << endl;
	}
	else {
		cerr << RED << "[FAIL] " << RESET << message << " (Expected: " << expected << ", Actual: " << actual << ")" << endl;
	}
}

static void assertEqualInt(int actual, int expected, const char* message) {
	if (actual == expected) {
		cout << GREEN << "[PASS] " << RESET << message << endl;
	}
	else {
		cerr << RED << "[FAIL] " << RESET << message << " (Expected: " << expected << ", Actual: " << actual << ")" << endl;
	}
}


