/*
 * database.h
 *
 *  Created on: 11 февр. 2020 г.
 *      Author: goncharov
 */

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
