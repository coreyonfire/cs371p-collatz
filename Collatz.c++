// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------
#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif



#include <cassert>  // assert
#include <iostream> // endl, istream, ostream, cin, cout, ios_base
#include <map> //map
#include <vector> //vector
#include "Collatz.h"

using namespace std;


//turn on debug messages
bool DEBUG = 0;
//select recursive or iterative mode
bool RECURSIVE = 1;

//vector declarations
static vector<unsigned> cycleMap(1, 0);
static map<int, int> greaterMap;

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

int collatz_recursive_helper(unsigned current, int length) {
	if (current != 1) {
		int t = 0;
		assert(current > 0);
		if (current < cycleMap.size()) t = cycleMap[current];
		else t = greaterMap[current];
		if (t != 0) {
			length += t - 1;
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
			if (current < cycleMap.size()) cycleMap[current] = length;
			else greaterMap[current] = length;
			return ++length + skipped;
		}
	}
	else return 1;
}

int collatz_eval_recursive(int i, int j) {
	int max = 0;
	int temp;
	cycleMap.resize(j*5, 0);
	while (i <=j) {
		temp = collatz_recursive_helper(i, 1);
		if (temp > max) max = temp;
		i++;
	}
	return max;
}

int collatz_eval_iterative(int i, int j) {
	int currentLength = 1;
	unsigned current;
	int max = 0, t = 0;
	cycleMap.resize(j*5, 0);
	while (i <= j) {
		current = i;
		while(current != 1) {
			//get value from map or vector
			assert (current > 0);
			if (current < cycleMap.size()) {
					t = cycleMap.at(current);
				}	
			else t = greaterMap[current];
			if (t == 0) {
				//value not found, it's not in the cache!
				if (current%2) {
					current = (3*(current)+1)/2;
					currentLength++;
				}
				else current = current/2;
				currentLength++;
			}
			else {
				//it was in the cache, just send that back
				currentLength += t - 1;
				break;
			}
			
		}
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
	if (i < j/2) i = j/2;
	//RECURSIVE VERSION
	if (i < j) v = collatz_eval_iterative(i, j);
	else v = collatz_eval_iterative (j, i);
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
        collatz_print(w, i, j, v);
	}
}


