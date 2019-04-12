/*
 * test_framework.cpp
 *
 *  Created on: 12 апр. 2019 г.
 */

#include "test_runner.h"

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

TestRunner::~TestRunner() {
  if (fail_count > 0) {
    cerr << fail_count << " unit tests failed. Terminate" << endl;
    exit(1);
  }
}
