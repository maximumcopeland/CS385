/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Max Copeland
 * Date        : 9/25/17
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (unsigned int i = 0; i < s.length(); i++) {
        if (!islower(s[i])) {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

    int storage = 0;                        // Storage will work as a bitmap to show what values have been encountered
    for (unsigned int i=0; i<s.length(); i++) {
        int temp = s[i] - 'a';              // Gives an int value corresponding to a=0, b=1, c=2, etc.
        if((storage & (1 << temp)) > 0) {   // If letter has already been encountered, 
            return false;                   // storage & (1 << temp) will return a value != 0
        }
        storage = storage | (1 << temp);    // Assuming no repeats, adds 1 bit to storage to take corresponding letter's place
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    // Check for error
    // No input arguments or too many inputs
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

    // Bad input
    if (!is_all_lowercase(argv[1])) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    // Output result
    if (all_unique_letters(argv[1])) {
        cout << "All letters are unique." << endl;
    }
    else {
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}
