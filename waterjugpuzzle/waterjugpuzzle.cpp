/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Max Copeland
 * Date        : 10/18/17
 * Description : Solves the water jug puzzle using breadth-first search
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/

 // (amount != 1? "gallons" : "gallon") <- Ternary Operator
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cctype>
#include <queue>
#include <map>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    // Return value of a jug
    int get(int s) {
        switch (s) {
            case 0:
                return a;
            case 1:
                return b;
            case 2:
                return c;
            default:
                return 0;
        }
    }

    // Override equals operator
    bool operator==(const State &other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};


vector<int> caps;
vector<int> goals;
queue<State> q;
bool **visited;

// Pour function
State pour(State s, int from, int to) {
    int amt = min(caps[to]-s.get(to), s.get(from));
    if (amt != 0) {
        int to2 = s.get(to) + amt;
        int from2 = s.get(from) - amt; 
        if (from == 0 && to == 1) { // Pour from A to B
            State s2(from2, to2, s.get(2));
            s2.directions = s.directions;
            s2.directions.push_back("Pour " + std::to_string(amt) + (amt != 1? " gallons" : " gallon") + " from A to B. " + s2.to_string());
            return s2;
        }
        if (from == 0 && to == 2) { // Pour from A to C
            State s2(from2, s.get(1), to2);
            s2.directions = s.directions;
            s2.directions.push_back("Pour " + std::to_string(amt) + (amt != 1? " gallons" : " gallon") + " from A to C. " + s2.to_string());
            return s2;
        }
        if (from == 1 && to == 0) { // Pour from B to A
            State s2(to2, from2, s.get(2));
            s2.directions = s.directions;
            s2.directions.push_back("Pour " + std::to_string(amt) + (amt != 1? " gallons" : " gallon") + " from B to A. " + s2.to_string());
            return s2;
        }
        if (from == 1 && to == 2) { // Pour from B to C
            State s2(s.get(0), from2, to2);
            s2.directions = s.directions;
            s2.directions.push_back("Pour " + std::to_string(amt) + (amt != 1? " gallons" : " gallon") + " from B to C. " + s2.to_string());
            return s2;
        }
        if (from == 2 && to == 0) { // Pour from C to A
            State s2(to2, s.get(1), from2);
            s2.directions = s.directions;
            s2.directions.push_back("Pour " + std::to_string(amt) + (amt != 1? " gallons" : " gallon") + " from C to A. " + s2.to_string());
            return s2;
        }
        if (from == 2 && to == 1) { // Pour from C to B
            State s2(s.get(0), to2, from2);
            s2.directions = s.directions;
            s2.directions.push_back("Pour " + std::to_string(amt) + (amt != 1? " gallons" : " gallon") + " from C to B. " + s2.to_string());
            return s2;
        }
    }
    return s;
}

// Performs bfs search to find solution if it exists
State bfs(State start, State target) {
    // Store seen states so they're not revisited
    q.push(start);

    // Begin the pain
    while (!q.empty()) {
        // Get the state at the front of the queue
        State top = q.front();
        q.pop();

        // Check if we've reached our goal
        if (top == target) {
            return top;
        }
        
        // Pour from C to A 
        State next = pour(top, 2, 0);
        if (visited[next.get(0)][next.get(1)] == 0) {
            visited[next.get(0)][next.get(1)] = 1; // We have visited it
            q.push(next);
        }

        // Pour from B to A 
        next = pour(top, 1, 0);
        if (visited[next.get(0)][next.get(1)] == 0) {
            visited[next.get(0)][next.get(1)] = 1; // We have visited it
            q.push(next);
        }

        // Pour from C to B 
        next = pour(top, 2, 1);
        if (visited[next.get(0)][next.get(1)] == 0) {
            visited[next.get(0)][next.get(1)] = 1; // We have visited it
            q.push(next);
        }

        // Pour from A to B 
        next = pour(top, 0, 1);
        if (visited[next.get(0)][next.get(1)] == 0) {
            visited[next.get(0)][next.get(1)] = 1; // We have visited it
            q.push(next);
        }

        // Pour from B to C 
        next = pour(top, 1, 2);
        if (visited[next.get(0)][next.get(1)] == 0) {
            visited[next.get(0)][next.get(1)] = 1; // We have visited it
            q.push(next);
        }

        // Pour from A to C 
        next = pour(top, 0, 2);
        if (visited[next.get(0)][next.get(1)] == 0) {
            visited[next.get(0)][next.get(1)] = 1; // We have visited it
            q.push(next);
        }
    }
    return start;
}

int main(int argc, char * const argv[]) {
    // No inputs or too many inputs
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    // Check inputs as valid integers
    istringstream iss;
    int a;
    for (int i = 1; i <= 3; i++) {
        iss.str(argv[i]);
        if (!(iss >> a) || a <= 0) {
            cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char) ('@'+i) << "." << endl;
            return 1;
        }
        caps.push_back(a);
        iss.clear();
    }
    for (int i = 4; i<= 6; i++) {
        iss.str(argv[i]);
        if (!(iss >> a) || a < 0) {
            cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << (char) ('@'-3+i) << "." << endl;
            return 1;
        }
        goals.push_back(a);
        iss.clear();
    }

    // Check goals are valid
    for (int i = 0; i <= 2; i++) {
        if (caps[i] < goals[i]) {
            cerr << "Error: Goal cannot exceed capacity of jug " << (char) ('A'+i) << "." << endl;
            return 1;
        }
    }

    // Check amount of water in goal adds up
    if ((goals[0] + goals[1] + goals[2]) != caps[2]) {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    
    // Stores capacitys and goals as states
    State start(0,0,caps[2]);
    State goal(goals[0],goals[1],goals[2]);

    // Checks if already solved 
    if (start == goal) {
        cout << "Initial state. " + start.to_string() << endl;
        return 0;
    }
    
    // Initialize Visited
    visited = new bool*[caps[0]+1];
    for (int i = 0; i <= caps[0]+1; i++) {
        visited[i] = new bool[caps[1]+1];
        for (int j = 0; j<= caps[1]+1; j++) {
            visited[i][j] = false;
        }
    }

    // Run BFS
    start.directions.push_back("Initial state. " + start.to_string());
    State sol = bfs(start, goal);
    if (sol == start) {
        cout << "No solution." << endl;
    }
    else {
        for (unsigned int i = 0; i < sol.directions.size(); i++) {
            cout << sol.directions[i] << endl;
        }
    }

    // Destructor for visited
    for (int i = 0; i < caps[0]+1; i++) {
        delete[] visited[i];
    }
    delete[] visited;

    return 0;
}