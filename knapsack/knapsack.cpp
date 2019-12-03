/*******************************************************************************
 * Name        : knapsack.cpp
 * Author      : Max Copeland
 * Date        : 12/4/17
 * Description : 0-1 Knapsack
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Item {
    unsigned int item_number, weight, value;
    string description;
    
    explicit Item(const unsigned int item_number,
                    const unsigned int weight,
                    const unsigned int value,
                    const string &description) :
                        item_number(item_number),
                        weight(weight),
                        value(value),
                        description(description) { }

    friend std::ostream& operator<<(std::ostream& os, const Item &item) {
        os << "Item " << item.item_number << ": " << item.description
            << " (" << item.weight
            << (item.weight == 1 ? " pound" : " pounds") << ", $"
            << item.value << ")";
        os.flush();
        return os;
    }
};

void knapsack(const vector<Item> &items, int cap) {
    // Initialize the lookup table
    int **table;
    int r = items.size();
    int c = cap;
    table = new int*[r+1];
    for (int i = 0; i <= r; ++i) {
        table[i] = new int[c+1];
        for (int j = 0; j <= c; ++j) {
            table[i][j] = 0;
        }
    }
    
    // Create the lookup table
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            int remSpace = j - items[i-1].weight;
            if (remSpace < 0) {
                table[i][j] = table[i-1][j];
            }
            else {
                table[i][j] = max((unsigned int)table[i-1][j], (unsigned int)items[i-1].value + (unsigned int)table[i-1][remSpace]);
            }
        }
    }

    int maxLoot = table[r][c];
    vector<Item> loot;
    int maxWeight = 0;

    // Backtrack
    while (r && c) {
        if (table[r][c] > table[r-1][c]) {
            loot.push_back(items[r-1]);
            maxWeight += items[r-1].weight;
            c -= items[r-1].weight;
        }
        --r;
    }
    r = items.size();
    c = cap;

    // Delete the table
    for (int i = 0; i <= r; ++i) {
        delete[] table[i];
    }
    delete[] table;

    // Output
    // Candidate items
    cout << "Candidate items to place in knapsack:" << endl;
    for (int i = 0; i < r; ++i) {
        cout << "   " << items[i] << endl;
    }
    cout << "Capacity: "  << cap  <<  (cap != 1? " pounds" : " pound") << endl;
    
    // Loot
    if (loot.size() == 0) {
        cout << "Items to place in knapsack: None" << endl;
    }
    else {
        cout << "Items to place in knapsack:" << endl;
        for (int i = (int)loot.size()-1; i >= 0; --i) {
            cout << "   " << loot[i] << endl;
        }
    }
    cout << "Total weight: " << maxWeight << (maxWeight != 1? " pounds" : " pound") << endl;
    cout << "Total value : $" << maxLoot << endl;


}

int main(int argc, char *argv[]) {
    // Command line parsinng
    int cap;
    // No arguments or too many arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <capacity> <filename>" << endl;
        return 1;
    }

    // Invalid capacity
    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k < 0 ) {
        cerr << "Error: Bad value '" << argv[1] << "' for capacity." << endl;
        return 1;
    }
    iss.clear();
    cap = k;

    // Valid capacity, but missing file
    ifstream input (argv[2]);
    if(!input) {
        cerr << "Error: Cannot open file '" << argv[2] << "'." << endl;
        return 1;
    }

    // Input file parsinng
    vector<Item> list; // Final list of items
    vector<string> item; // Temporary vector for parsing
    string temp, val;
    int numItems = 0;
    int w, v;
    while (getline(input, temp)) {
        iss.str(temp);
        ++numItems;\
        
        // Load each field into item temporarily
        while (getline(iss, val, ',')) {
            item.push_back(val);
            iss.clear();
        }
        iss.clear();

        // Check for 3 fields
        if (item.size() != 3) {
            cerr << "Error: Line number " << numItems << " does not contain 3 fields." << endl;
            input.close();
            return 1;
        }
        
        // Check the weight
        iss.str(item[1]);
        if (!(iss >> w) || (w <= 0)) {
            cerr << "Error: Invalid weight '" << item[1] << "' on line number " << numItems << "." << endl;
            input.close();
            return 1;
        }
        iss.clear();

        // Check the value
        iss.str(item[2]);
        if (!(iss >> v) || (v <= 0)) {
            cerr << "Error: Invalid value '" << item[2] << "' on line number " << numItems << "." << endl;
            input.close();
            return 1;
        }
        iss.clear();

        list.push_back(Item(numItems, w, v, item[0]));
        item.clear();
    }
    input.close();
    
    // Call knapsack
    knapsack(list, cap);
    
    return 0;
}