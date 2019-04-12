/*
 * test_framework.cpp
 *
 *  Created on: 12 апр. 2019 г.
 */

#include "test_framework.h"

template<class T, class U>
void AssertEqual(const T& t, const U& u,
    const string& hint)
{
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u
       << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

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
