#pragma once

//using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

class Node {
public:
	virtual ~Node ();
  virtual int Evaluate() const = 0;

};

class DateComparisonNode : public Node {
public:
	DateComparisonNode (const Comparison& cmp, const Date& date) : Node(), cmp_(cmp), date_(date) {};
private:
	Comparison cmp_;
	Date date_;
};

