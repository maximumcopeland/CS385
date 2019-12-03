/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Max Copeland
 * Version     : 1.0
 * Date        : 11/3/2017
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long inversions = 0;
    for (int i = 0; i < length-1; i++) {
        for (int j = i+1; j < length; j++) {
            if (array[i] > array[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}


/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int* scratch = new int[length];
    long inversions = mergesort(array, scratch, 0, length-1);
    delete[] scratch;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    int mid, L, H = 0;
    long inversions = 0;
    if (low < high) {
        mid = low + (high - low)/2;
        inversions += mergesort(array, scratch, low, mid);
        inversions += mergesort(array, scratch, mid+1, high);
        L = low;
        H = mid+1;
        for (int i = low; i <= high; i++) {
            if (L <= mid && (H > high || array[L] <= array[H])) {
                scratch[i] = array[L];
                L++;
            }
            else {
                scratch[i] = array[H];
                H++;
                inversions += mid-L+1;
            }
        }
        for (int i = low; i <= high; i++) {
            array[i] = scratch[i];
        }
    }
    return inversions;
}

int main(int argc, char *argv[]) {
    // Parse command-line argument
    // If there are too many inputs
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }

    // If unrecognized command is used
    string command;
    if (argc > 1) {
        istringstream isss;
        isss.str(argv[1]);
        isss >> command;
        if (command != "slow"){
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return 1;
        }
        isss.clear();
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // If no integers recieved
    if (values.empty()) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // Find inversions with method dependant on command
    if (command == "slow") {
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }
    else {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }
    return 0;
}
