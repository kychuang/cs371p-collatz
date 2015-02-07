#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

#include <iostream> // cin, cout
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

using namespace std;

int collatz_cache [100000] = { };       // a cache containing the cycle_lengths of collatz numbers as indicated by index
                                        // all values in cache initialized to 0. collatz_cache[0] remains empty forever.

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// cycle_length
// ------------

/* This helper function copied from the examples in class
   computes cycle length of a single collatz number */

int cycle_length (int n) {
    unsigned int c = 1;
    int original_n = n; //saves value of n so cycle_length of n can be cached.
    
    /* If the number has been cached, load the cached value
       and terminate the loop. */
    while (n > 1) {
        if((n < 100000) && (collatz_cache[n] > 0)){     //check to see if n is in the cache already
            if(n == original_n)
                c = collatz_cache[n];
            else
                c = c + collatz_cache[n] - 1;

            break;
        }
        else {
        	if ((n % 2) == 0)
            n = (n / 2);
        	else
            	n = (3 * n) + 1;
    		++c;
    	}
    }
    
	if(original_n < 100000)
    	collatz_cache[original_n] = c;

    return c;
}


// ------------
// collatz_eval
// ------------

/* This function evaluates cycle length for all integers in range [i,j]
   and returns the largest cycle length in range [i,j] */

int collatz_eval (int i, int j) {
    // <your code>  
    int maxCycleLength = 1;     //stores the largest cycle length of all collatz numbers in the range of i to a
    int tempCycleLength;    //stores the cycle length of the most recently computed collatz number
    for (int a= min(i,j); a <= max(i,j); a++) {
        tempCycleLength = cycle_length(a);
        if (maxCycleLength < tempCycleLength)
            maxCycleLength = tempCycleLength;
    }
    
    return maxCycleLength;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}