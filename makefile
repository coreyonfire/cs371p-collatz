RunCollatz: Collatz.h Collatz.c++ RunCollatz.c++
	g++ -pedantic -std=c++0x -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz

run: RunCollatz
	RunCollatz < RunCollatz.in

runv: RunCollatz
	valgrind RunCollatz < RunCollatz.in

diff: RunCollatz
	RunCollatz < RunCollatz.in > RunCollatz.tmp
	diff RunCollatz.out RunCollatz.tmp
	rm RunCollatz.tmp

TestCollatz: Collatz.h Collatz.c++ TestCollatz.c++
	g++ -lcppunit -ldl -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz

test: TestCollatz
	TestCollatz

testv: TestCollatz
	valgrind TestCollatz

clean:
	rm -f RunCollatz
	rm -f TestCollatz
	rm -f *.tmp