// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz.c++.app
    % valgrind TestCollatz.c++.app >& TestCollatz.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

struct TestCollatz : CppUnit::TestFixture {
    // ----
    // read ALL TESTS WRITTEN
    // ----

    void test_read () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);
		
        std::istringstream t("50 100\n");
        const bool e = collatz_read(t, i, j);
        CPPUNIT_ASSERT(e == true);
        CPPUNIT_ASSERT(i ==    50);
        CPPUNIT_ASSERT(j ==   100);
		
        std::istringstream q("1 1\n");
        const bool c = collatz_read(q, i, j);
        CPPUNIT_ASSERT(c == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   1);
	}

    // ----
    // eval ALL TESTS WRITTEN
    // ----

    void test_eval_1 () {
        const int v = collatz_eval(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_2 () {
        const int v = collatz_eval(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_3 () {
        const int v = collatz_eval(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_4 () {
        const int v = collatz_eval(900, 1000);
        CPPUNIT_ASSERT(v == 174);
	}

    // -----
    // print ALL TESTS WRITTEN
    // -----

    void test_print () {
        std::ostringstream w, v, x;
        collatz_print(w, 1, 10, 20);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n");
		
		collatz_print(v, 3, 5, 20);
		CPPUNIT_ASSERT(v.str() == "3 5 20\n");
		
		collatz_print(x, 258, 5, 20);
		CPPUNIT_ASSERT(x.str() == "258 5 20\n");
	}

    // -----
    // solve ALL TESTS WRITTEN
    // -----

    void test_solve () {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w, v, x;
        collatz_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
		
		std::istringstream s("1 43\n200 42\n52 72\n");
		collatz_solve(s, v);
        CPPUNIT_ASSERT(v.str() == "1 43 112\n200 42 125\n52 72 113\n");
		
		std::istringstream t("1 500\n1 1000\n1 10000\n");
		collatz_solve(t, x);
        CPPUNIT_ASSERT(x.str() == "1 500 144\n1 1000 179\n1 10000 262\n");
	}
	
	// -----
	// eval_iterative
	// -----
	
	void test_eval_iterative_1 () {
        const int v = collatz_eval_iterative(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_iterative_2 () {
        const int v = collatz_eval_iterative(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_iterative_3 () {
        const int v = collatz_eval_iterative(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_iterative_4 () {
        const int v = collatz_eval_iterative(900, 1000);
        CPPUNIT_ASSERT(v == 174);
	}
	
	// -----
	// eval_recursive
	// -----

	void test_eval_recursive_1 () {
        const int v = collatz_eval_recursive(1, 10);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_recursive_2 () {
        const int v = collatz_eval_recursive(100, 200);
        CPPUNIT_ASSERT(v == 125);}

    void test_eval_recursive_3 () {
        const int v = collatz_eval_recursive(201, 210);
        CPPUNIT_ASSERT(v == 89);}

    void test_eval_recursive_4 () {
        const int v = collatz_eval_recursive(900, 1000);
        CPPUNIT_ASSERT(v == 174);
	}
	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCollatz);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_recursive_1);
    CPPUNIT_TEST(test_eval_recursive_2);
    CPPUNIT_TEST(test_eval_recursive_3);
    CPPUNIT_TEST(test_eval_recursive_4);
    CPPUNIT_TEST(test_eval_iterative_1);
    CPPUNIT_TEST(test_eval_iterative_2);
    CPPUNIT_TEST(test_eval_iterative_3);
    CPPUNIT_TEST(test_eval_iterative_4);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestCollatz.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCollatz::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}