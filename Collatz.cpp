// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <map> //map
#include "Collatz.h"

using namespace std;


//turn on debug messages
bool DEBUG = 1;

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

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    //BEGIN MY CODE
    int v = 1;
	int currentLength = 1;
	int current;
	map<int, int> cycleMap;
	if (j < i) {
		//switch the numbers around for an ascending range
		int swap = j;
		j = i;
		i = swap;
	}
	assert(i <= j);
	if (DEBUG) cout << "finding longest cycle between " << i << " and " << j << endl; 
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
		if (currentLength > v) v = currentLength;
		currentLength = 1;
		i++;
	}
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
