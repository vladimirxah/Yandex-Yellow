/*
 * database.h
 *
 *  Created on: 25 янв. 2020 г.
 *      Author: goncharov
 */

#pragma once

#include "date.h"

#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;

class Database {
public:
  void Add(const Date& date, const string& event);

  bool DeleteEvent(const Date& date, const string& event);

  int DeleteDate(const Date& date);

  int RemoveIf (const ?);

  void FindIf (const ?);

  void Last (const ?);

  set<string> Find(const Date& date);

  ostream Print(ostream& ostr);

private:
  map<Date, set<string>> storage;
};
