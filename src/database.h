/*класс Database, который представляет собой базу данных, — вы должны сами создать его публичный интерфейс, основываясь на том, как он используется в функции main*/
/*database.h/cpp — эти файлы должны содержать объявление и определение класса Database;*/


#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>

#include "date.h"
#include "node.h"

using namespace std;

typedef pair<Date, string> record;

class Database {
public:
	void Add (const Date& date, const string& event);
	ostream& Print (ostream& os) const;
	int RemoveIf (function<bool(const Date& date, const string& event)> predicate); //std::function<int(int)> x
	// на вход принимается [ParseCondition(is)](const Date& date, const string& event) {  return condition->Evaluate(date, event); }

	vector<record> FindIf (function<bool(const Date& date, const string& event)> predicate) const;
//	не уверен, какой тип должен отдавать метод. По идее вектор пар может подойти. В main по отданному результату итерируются методом RangeBasedFor и выводят << в cout.

	string Last (const Date& date) const;
	unsigned int Size() const;

private:
	map<Date, set<string>> db_set_;
	map<Date, vector<string>> db_vec_;

};

// записи (дата и событие) будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const record& rec);
