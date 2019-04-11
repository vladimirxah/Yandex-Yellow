#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
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
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Rational {
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

  Rational();
  Rational(int numerator, int denominator) {
  }

  int Numerator() const {
  }

  int Denominator() const {
  }
};

void TestBlank () {
	Rational r;
	AssertEqual(r.Numerator(), 0, "Zero num for blank rational");
	AssertEqual(r.Denominator(), 1, "One denum for blank rational");
}

void TestZeros () {
	Rational r(0, 50);
	AssertEqual(r.Numerator(), 0, "Zero num for zero rational");
	AssertEqual(r.Denominator(), 1, "One denum for zero rational");
	Rational r2(0, -50);
	AssertEqual(r2.Numerator(), 0, "Zero num for -zero rational");
	AssertEqual(r2.Denominator(), 1, "One denum for -zero rational");
}

void TestFractRed () {
	Rational r(4, 6);
	AssertEqual(r.Numerator(), 2, "4/6 to 2/3, num");
	AssertEqual(r.Denominator(), 3, "4/6 to 2/3, denum");
}

void TestNormal () {
	Rational r(5, 6);
	AssertEqual(r.Numerator(), 5, "just 5/6, num");
	AssertEqual(r.Denominator(), 6, "just 5/6, denum");
	Rational r2(-7, -10);
	AssertEqual(r2.Numerator(), 7, "just -7/-10, num");
	AssertEqual(r2.Denominator(), 10, "just -7/-10, denum");
}

void TestNeg () {
	Rational r(-5, 6);
	AssertEqual(r.Numerator(), -5, "neg -5/6, num");
	AssertEqual(r.Denominator(), 6, "neg -5/6, denum");
	Rational r2(7, -10);
	AssertEqual(r2.Numerator(), -7, "neg 7/-10, num");
	AssertEqual(r2.Denominator(), 10, "neg 7/-10, denum");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestZeros, "TestBlank");
  runner.RunTest(TestBlank, "TestZeros");
  runner.RunTest(TestFractRed, "TestFractRed");
  runner.RunTest(TestNormal, "TestNormal");
  runner.RunTest(TestNeg, "TestNeg");
  // добавьте сюда свои тесты
  return 0;
}

//EXAMPLE
/*
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
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
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

void TestPredefined() {
  AssertEqual(Rational(1, 1).Numerator(), 1, "Canonical form of 1/1 is 1/1");
  AssertEqual(Rational(1, 1).Denominator(), 1, "Canonical form of 1/1 is 1/1");
  AssertEqual(Rational(3, 5).Numerator(), 3, "Canonical form of 3/5 is 3/5");
  AssertEqual(Rational(3, 5).Denominator(), 5, "Canonical form of 3/5 is 3/5");
  AssertEqual(Rational(2147483647, 2147483647).Numerator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
  AssertEqual(Rational(2147483647, 2147483647).Denominator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
  AssertEqual(Rational(-5, 4).Numerator(), -5, "Canonical form of -5/4 is -5/4");
  AssertEqual(Rational(-5, 4).Denominator(), 4, "Canonical form of -5/4 is -5/4");
  AssertEqual(Rational(5, -4).Numerator(), -5, "Canonical form of 5/-4 is -5/4");
  AssertEqual(Rational(5, -4).Denominator(), 4, "Canonical form of 5/-4 is -5/4");
  AssertEqual(Rational(-6, -2).Numerator(), 3, "Canonical form of -6/-2 is 3/1");
  AssertEqual(Rational(-6, -2).Denominator(), 1, "Canonical form of -6/-2 is 3/1");
  AssertEqual(Rational(21, 56).Numerator(), 3, "Canonical form of 21/56 is 3/8");
  AssertEqual(Rational(21, 56).Denominator(), 8, "Canonical form of 21/56 is 3/8");
  AssertEqual(Rational(0, 100).Numerator(), 0, "Canonical form of 0/100 is 0/1");
  AssertEqual(Rational(0, 100).Denominator(), 1, "Canonical form of 0/100 is 0/1");
  AssertEqual(Rational().Numerator(), 0, "Canonical form of default constructed is 0/1");
  AssertEqual(Rational().Denominator(), 1, "Canonical form of default constructed is 0/1");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPredefined, "TestPredefined");
  return 0;
}*/
