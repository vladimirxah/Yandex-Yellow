/*классы Node, EmptyNode, DateComparisonNode, EventComparisonNode и LogicalOperationNode — сформировать их иерархию и публичный интерфейс вам поможет анализ функций main и ParseCondition;*/
/*node.h/cpp — эти файлы должны содержать объявления и определения класса Node, а также всех его потомков (см. выше), которые представляют собой узлы абстрактного синтаксического дерева, формируемого функцией ParseCondition;*/

#pragma once

#include "date.h"

#include <memory>

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
  virtual bool Evaluate(const Date& date, const string& string)/* const = 0*/;
//  здесь может быть bool (если смотреть на сигнатуру Assert в файлах с тестами. Но может быть и int.
};

class EmptyNode : public Node {};

class DateComparisonNode : public Node {
public:
	DateComparisonNode (const Comparison& cmp, const Date& date) : Node(), cmp_(cmp), date_(date) {};

private:
	Comparison cmp_;
	Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode (const Comparison& cmp, const string& str) : Node(), cmp_(cmp), str_(str) {};

private:
	const Comparison cmp_;
	const string& str_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode (const LogicalOperation& logical_operation, shared_ptr<Node> left,
											shared_ptr<Node>& right) : Node(), logical_operation_(logical_operation), left_(left),
											right_(right) {};
private:
	const LogicalOperation logical_operation_;
	shared_ptr<Node> left_;
	shared_ptr<Node>& right_;
};
