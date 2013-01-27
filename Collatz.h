// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream

// ------------
// collatz_read
// ------------

/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool collatz_read (std::istream& r, int& i, int& j);

// ------------
// collatz_eval
// ------------

/**
 * Evaluates
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval (int i, int j);

/**
 * Computes the value iteratively
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval_recursive(int i, int j);

/**
 * Computes the value iteratively
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval_iterative(int i, int j);

// -------------
// collatz_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream& r, std::ostream& w);

#endif // Collatz_h