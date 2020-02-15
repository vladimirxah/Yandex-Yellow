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

// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date& lhs, const Date& rhs) {
  // воспользуемся тем фактом, что векторы уже можно сравнивать на <:
  // создадим вектор из года, месяца и дня для каждой даты и сравним их
//	auto tlhs = make_tuple (lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());

	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
				 make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}
