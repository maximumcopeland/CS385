/* Max Copeland
 * CS 385 Algorithms
 * Lab 7: Russian Peasant Multiplication
 * "I pledge my honor that I have abided by the Stevens Honor System"
 */

#include <iostream>
#include <sstream>

using namespace std;

unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n) {
    // assumes m > n
    unsigned long res = 0;
    unsigned long t = m;
       while (n > 0) {
            // If n is odd, add t to result
            if (n & 1) {
                res = res + t;
            }
            // Double t and halve n
            t <<= 1;
            n >>= 1;
        }
        return res;
}

int main(int argc, char * const argv[]) {
    // No inputs or too many inputs
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
        return 1;
    }

    // Check inputs as valid integers
    istringstream iss;
    int m,n;
    iss.str(argv[1]);
	if ( !(iss >> m) || m < 0 ) {
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 1;
	}
	iss.clear(); //Clear the error code
	iss.str(argv[2]);
	if ( !(iss >> n) || n < 0) {
		cerr << "Error: The second argument is not a valid nonnegative integer." << endl;
		return 1;
    }
    
    // Do the thing
    if (m > n) {
        cout << m << " x " << n << " = " << russian_peasant_multiplication(m,n) << endl;
    }
    else {
        cout << m << " x " << n << " = " << russian_peasant_multiplication(n,m) << endl;
    }
    return 0;
}