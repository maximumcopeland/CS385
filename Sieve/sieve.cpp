/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Max Copeland
 * Date        : 9/16/17
 * Description : Sieve of Eratosthenes
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve(limit);
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        // Prints prime numbers (max 80 characters per line) in right-aligned format
        const int max_prime_width = num_digits(max_prime_);
        const int primes_per_row = 80 / (max_prime_width + 1);
        
        int counter = 0;
        // If there are more than one rows
        if (num_primes_ >= primes_per_row) {
            for (int i = 0; i <= limit_ ; i++) {
                if (counter >= primes_per_row) {
                    cout << endl;
                    counter = 0;
                }
                if (is_prime_[i]) {
                    // If it's the last number for that row
                    if (counter == primes_per_row - 1) {
                        cout << setw(max_prime_width) << i;
                        counter++;
                    }
                    // If it's the last number for the set
                    else if (i == max_prime_) {
                        cout  << i;
                        counter++;
                    }
                    else {
                        cout << setw(max_prime_width) << i << " ";
                        counter++;
                    }
                }
            }
        }
        // Only one row; does not need right-alignment
        else {
            for (int i = 0; i<= limit_ ; i++) {
                if (is_prime_[i]) {
                    // If it's the last number for the set
                    if (i == max_prime_) {
                        cout  << i;
                        counter++;
                    }
                    else {
                        cout << i << " ";
                        counter++;
                    }
                }
            }
        }
        cout << endl;
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
        // Counts the number of primes that have been found and returns as an int
        int counter = 0;
        for (int i = 0; i < limit_; i++) {
            if (is_prime_[i]) {
                counter++;
            }
        }
        return counter;
    }

    int num_digits(int num) const {
        // Returns how many digits are in a number
        int counter = 1;
        while (num >= 10) {
            num = num/10;
            counter ++;
        }
        return counter;
    }

    void sieve(int n) {
        // Defines is_prime_ array
        is_prime_[0] = false;
        is_prime_[1] = false;
        for (int i = 2; i <= limit_; i++) {
            is_prime_[i] = true;
        }


        // Marks prime numbers in is_prime array
        for (int i = 2; i <= sqrt(n); i ++) {
            if (is_prime_[i]) {
                for (int j = pow(i,2); j <= n; j = j + i) {
                    is_prime_[j] = false;
                }
            }
        }

        // Define num_primes_ and max_prime
        num_primes_ = 0;
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i]) {
            		num_primes_++;
            		max_prime_ = i;
            }
        }

    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve primes(limit);
    cout << endl;
    cout << "Number of primes found: " << primes.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    primes.display_primes();
    return 0;
}
