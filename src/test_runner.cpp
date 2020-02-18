/*
 * test_runner.cpp
 *
 *  Created on: 25 янв. 2020 г.
 *      Author: gonchrov
 */

#include "test_runner.h"

#include <vector>

vector<int> h;

/*inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}*/

TestRunner::~TestRunner() {
	if (fail_count > 0) {
		cerr << fail_count << " unit tests failed. Terminate" << endl;
		exit(1);
	}
}
