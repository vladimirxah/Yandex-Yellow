/*класс Database, который представляет собой базу данных, — вы должны сами создать его публичный интерфейс, основываясь на том, как он используется в функции main*/
/*database.h/cpp — эти файлы должны содержать объявление и определение класса Database;*/

#pragma once

#include "date.h"

#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Database {
public:

private:
	map<Date, set<string>> db_set_;
	map<Date, vector<string>> db_vec_;

}
