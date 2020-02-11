/*
 * test_runner.cpp
 *
 *  Created on: 25 янв. 2020 г.
 *      Author: gonchrov
 */

#include "test_runner.h"

#include <vector>

vector<int> h;

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string& test_name) {
	try {
		func();
		cerr << test_name << " OK" << endl;
	} catch (runtime_error& e) {
		++fail_count;
		cerr << test_name << " fail: " << e.what() << endl;
	}
}

TestRunner::~TestRunner() {
	if (fail_count > 0) {
		cerr << fail_count << " unit tests failed. Terminate" << endl;
		exit(1);
	}
}
