#pragma once

#include <stdexcept>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Date {
public:
  // конструктор выбрасывает исключение, если его аргументы некорректны
  Date(int new_year, int new_month, int new_day);

  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;

private:
  int year;
  int month;
  int day;
};

// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date& lhs, const Date& rhs) {
  // воспользуемся тем фактом, что векторы уже можно сравнивать на <:
  // создадим вектор из года, месяца и дня для каждой даты и сравним их
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
				 make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

// непонятно, нужен ли этот оператор
bool operator==(const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
				 make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}
