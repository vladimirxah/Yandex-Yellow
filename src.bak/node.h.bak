#pragma once

#include "date.h"

#include <memory>

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
  virtual int Evaluate(const Date& date, const string& string)/* const = 0*/;

};

class DateComparisonNode : public Node {
public:
	DateComparisonNode (const Comparison& cmp, const Date& date) : Node(), cmp_(cmp), date_(date) {};
private:
	Comparison cmp_;
	Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode (const Comparison& cmp, const string& value) : Node(), cmp_(cmp), value_(value) {};
private:
	Comparison cmp_;
	string value_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode (const LogicalOperation& logical_operation, const shared_ptr<Node>& left,
												const shared_ptr<Node>& expression_to_parse) : Node(), logical_operation_ (logical_operation),
												left_(left), expression_to_parse_(expression_to_parse){};
private:
	LogicalOperation logical_operation_;
	shared_ptr<Node> left_;
	shared_ptr<Node> expression_to_parse_;
};

class EmptyNode : public Node {
public:
	EmptyNode () : Node() {};
};
