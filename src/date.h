/*класс Date, а также функцию ParseDate и оператор вывода в поток для класса Date.*/
/*date.h/cpp — эти файлы должны содержать объявления и определения класса Date, функции ParseDate и оператора вывода в поток для класса Date;*/

#pragma once

#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <tuple>

using namespace std;

class Date {
public:
  Date(int new_year, int new_month, int new_day);

  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;

private:
  int year;
  int month;
  int day;
};

Date ParseDate(istringstream& is); // Этой строки нет в "примере", добавлял я. Возможно надо реализовать в date.h
// функция должна выбрасывать invalid_argument& если формат даты неверный

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& stream, const Date& date);
