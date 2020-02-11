/*класс Database, который представляет собой базу данных, — вы должны сами создать его публичный интерфейс, основываясь на том, как он используется в функции main*/
/*database.h/cpp — эти файлы должны содержать объявление и определение класса Database;*/



#pragma once

#include "date.h"

#include <string>
#include <map>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

typedef pair<Date, string> record;

class Database {
public:
	void Add (const Date& date, const string& event);
	ostream Print (ostream& os) const;
	int RemoveIf (/*понять, что идет на выходе методов Evaluate для класса Node*/);
	// на вход принимается [ParseCondition(is)](const Date& date, const string& event) {  return condition->Evaluate(date, event); }

	vector<pair<Date, string>> FindIf (/*понять, что идет на выходе методов Evaluate для класса Node*/) const;
//	не уверен, какой тип должен отдавать метод. По идее вектор пар может подойти. В main по отданному результату итерируются методом RangeBasedFor и выводят << в cout.

	record Last (const Date& date) const;

private:
	map<Date, set<string>> db_set_;
	map<Date, vector<string>> db_vec_;

};

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const record& rec) {
	stream << rec.first << ' ' << rec.second;
  return stream;
}
