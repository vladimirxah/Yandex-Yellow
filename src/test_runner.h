/*
 * test_runner.h
 *
 *  Created on: 25 янв. 2020 г.
 *      Author: gonchrov
 */

#pragma once

#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const set<T>& s);
template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m);
template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint);
inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "(";
  bool first = true;
  for (const auto& x : v) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << ")";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

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

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (runtime_error& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
	}

  ~TestRunner();

private:
  int fail_count = 0;
};

/*
Add functions
void TestSomething () {
	AssertEqual(... , ...)
}

void TestAll () {
  TestRunner tr;
  tr.RunTest(TestSomething, "TestSomething");
}

int main() {
	TestAll();
	...
}
*/
