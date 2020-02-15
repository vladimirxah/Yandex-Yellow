/*
 * date.cpp
 *
 *  Created on: 11 февр. 2020 г.
 *      Author: gonchrov
 */

#include "date.h"

// конструктор выбрасывает исключение, если его аргументы некорректны
Date::Date(int new_year, int new_month, int new_day) {
	year = new_year;
	if (new_month > 12 || new_month < 1) {
		throw logic_error("Month value is invalid: " + to_string(new_month));
	}
	month = new_month;
	if (new_day > 31 || new_day < 1) {
		throw logic_error("Day value is invalid: " + to_string(new_day));
	}
	day = new_day;
}

int Date::GetYear() const {
	return year;
}
int Date::GetMonth() const {
	return month;
}
int Date::GetDay() const {
	return day;
}

Date ParseDate(istringstream& is) {
	string istr;
	is >> istr;
	istringstream date_stream(istr);
  bool ok = true;

  int year;
  ok = ok && (date_stream >> year);
  ok = ok && (date_stream.peek() == '-') && year >= 0;
  date_stream.ignore(1);

  int month;
  ok = ok && (date_stream >> month);
  ok = ok && (date_stream.peek() == '-') && month > 0;
  date_stream.ignore(1);

  int day;
  ok = ok && (date_stream >> day);
  ok = ok && date_stream.eof() && day > 0;

  if (!ok) {
    throw logic_error("Wrong date format: " + istr);
  }
  return Date(year, month, day);
}
