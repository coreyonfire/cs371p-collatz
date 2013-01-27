// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------	


#include <cassert>  // assert
#include <iostream> // endl, istream, ostream, cin, cout, ios_base
#include <map> //map

using namespace std;


//turn on debug messages
bool DEBUG = 0;
//select recursive or iterative mode
bool RECURSIVE = 1;
static map<unsigned, unsigned> cycleMap;
// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

int collatz_recursive_helper(int current, int length) {
	if (DEBUG) cout << "current: " << current << endl;
	if (current != 1) {
		int t = cycleMap[current];
		if (t != 0) {
			length += t - 1;
			if (DEBUG) cout << "found previous entry for " << current << ": " << t << ", returning " << length << endl;
			return length;
		}
		else {
			bool skipped = 0;
			if (current % 2) {
				current = (3 * (current) + 1) / 2;
				skipped++;
			}
			else current = current / 2;
			length = collatz_recursive_helper(current, length);
			cycleMap[current] = length;
			return ++length + skipped;
		}
	}
	else return 1;
}

int collatz_eval_recursive(int i, int j) {
	int max = 0;
	int temp;
	while (i <=j) {
		if (DEBUG) cout << "finding cycle for " << i << endl;
		temp = collatz_recursive_helper(i, 1);
		if (DEBUG) cout << "length is " << temp << endl;
		if (temp > max) max = temp;
		i++;
	}
	return max;
}

int collatz_eval_iterative(int i, int j) {
	int currentLength = 1;
	int current;
	int max = 0;
	while (i <= j) {
		if (DEBUG) cout << "finding cycle for " << i << endl;
		current = i;
		while(current != 1) {
			assert (current > 0);
			if (DEBUG) cout << current << ", currentLength is " << currentLength << endl;
			if (cycleMap[current] != 0) {
				if (DEBUG) cout << "found a previous cycle for " << i << ", adding " << cycleMap[current] << endl;
				currentLength += cycleMap[current] - 1;
				current = 1;
				break;
			}
			else if (current%2) current = 3*(current)+1;
			else current = current/2;
			currentLength++;
		}
		if (DEBUG) cout << "cycle length for " << i << " is " << currentLength << endl;
		cycleMap[i] = currentLength;
		if (currentLength > max) max = currentLength;
		currentLength = 1;
		i++;
	}
	return max;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    //BEGIN MY CODE
    int v = 1;
	if (j < i) {
		//switch the numbers around for an ascending range
		int swap = j;
		j = i;
		i = swap;
	}
	assert(i <= j);
	if (DEBUG) cout << "finding longest cycle between " << i << " and " << j << endl; 
	//RECURSIVE VERSION
	if (RECURSIVE) v = collatz_eval_recursive(i, j);

	//ITERATIVE VERSION
	else v = collatz_eval_iterative(i, j);
	//END MY CODE
    assert(v > 0);
    return v;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}



// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}