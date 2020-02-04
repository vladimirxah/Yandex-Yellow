#pragma once

//using namespace std;

struct Node {
	virtual ~Node ();
  virtual int Evaluate() const = 0;

};
