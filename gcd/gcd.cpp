/* Max Copeland
 * CS 385 Algorithms
 * Assignment 1: GCD With loop and recursion
 * "I pledge my honor that I have abided by the Stevens Honor Code"
 */
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

int gcdLoop(int x, int y){
	int a = abs(x);
	int b = abs(y);
	if (a == b)
		return a;
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	while(a != b){
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return a;
}

int gcdRecur(int x, int y){
	int a = abs(x);
	int b = abs(y);
	if (a == b)
		return a;
	if (a == 0)
			return b;
		if (b == 0)
			return a;
	if (a>b)
		return gcdRecur(a-b, b);
	return gcdRecur(a, b-a);
}

int main(int argc, char* const argv[]) {
	int m, n;
	istringstream iss;

	if (argc!=3) {
		//There are not 3 arguments
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if ( !(iss >> m) ) {
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear(); //Clear the error code
	iss.str(argv[2]);
	if ( !(iss >> n) ) {
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}

	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcdLoop(m, n) << endl;
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcdRecur(m, n) << endl;
	return 0;
}
