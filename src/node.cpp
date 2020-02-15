/*
 * node.cpp
 *
 *  Created on: 11 февр. 2020 г.
 *      Author: gonchrov
 */

#include "node.h"

bool DateComparisonNode::Evaluate(const Date& date, const string& str) {
//	надо переписать через оператор switch, для enums он легко пишется
	bool ev = false;
/*	if (cmp_ == Comparison::Less) {
		ev = date < date_;
	} else if (cmp_ == Comparison::LessOrEqual) {
		ev = date <= date_;
	} else if (cmp_ == Comparison::Greater) {
		ev = date > date_;;
	} else if (cmp_ == Comparison::GreaterOrEqual) {
		ev = date >= date_;
	} else if (cmp_ == Comparison::Equal) {
		ev = date == date_;
	} else if (cmp_ == Comparison::NotEqual) {
		ev = date != date_;
	}
	return ev;*/

	switch (cmp_)
	{
	case Comparison::Less:
		ev = date < date_;
		break;
	case Comparison::LessOrEqual:
		ev = date <= date_;
		break;
	case Comparison::Greater:
		ev = date > date_;
		break;
	case Comparison::GreaterOrEqual:
		ev = date >= date_;
		break;
	case Comparison::Equal:
		ev = date = date_;
		break;
	case Comparison::NotEqual:
		ev = date != date_;
		break;
	}
	return ev;
}

bool EventComparisonNode::Evaluate(const Date& date, const string& str) {
	bool ev = false;
	switch (cmp_)
	{
	case Comparison::Less:
		ev = str < str_;
		break;
	case Comparison::LessOrEqual:
		ev = str <= str_;
		break;
	case Comparison::Greater:
		ev = str > str_;
		break;
	case Comparison::GreaterOrEqual:
		ev = str >= str_;
		break;
	case Comparison::Equal:
		ev = str = str_;
		break;
	case Comparison::NotEqual:
		ev = str != str_;
		break;
	}
	return ev;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& str) {
	switch (logical_operation_)
	{
	case LogicalOperation::Or:
		return left_->Evaluate(date, str) || right_->Evaluate(date, str);
	case LogicalOperation::And:
		return left_->Evaluate(date, str) && right_->Evaluate(date, str);
	}
}
/*
private:
	const LogicalOperation logical_operation_;
	shared_ptr<Node>& left_;
	shared_ptr<Node>& right_;*/
