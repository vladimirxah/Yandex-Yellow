/*
 * main.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 *
Часть 1. Группировка по символу
Напишите функцию FindStartsWith:

*принимающую отсортированный набор строк в виде итераторов range_begin, range_end и один символ prefix;
*возвращающую диапазон строк, начинающихся с символа prefix, в виде пары итераторов.

		template <typename RandomIt>
		pair<RandomIt, RandomIt> FindStartsWith(
				RandomIt range_begin, RandomIt range_end,
				char prefix);

Если итоговый диапазон пуст, его границы должны указывать на то место в контейнере, куда можно без нарушения порядка сортировки вставить любую строку, начинающуюся с символа prefix (подобно алгоритму equal_range). Гарантируется, что строки состоят лишь из строчных латинских букв и символ prefix также является строчной латинской буквой.

Поиск должен осуществляться за логарифмическую сложность — например, с помощью двоичного поиска.

Подсказка
К символам (char) можно прибавлять или вычитать числа, получая таким образом следующие или предыдущие буквы в алфавитном порядке. Например, для строки s выражение --s[0] заменит её первую букву на предыдущую.

Обратите внимание, что выражение 'a' + 1 имеет тип int и поэтому может понадобиться привести его к типу char с помощью static_cast.
 */

/*Напишите более универсальный вариант функции FindStartsWith, принимающий в качестве префикса произвольную строку, состоящую из строчных латинских букв.*/

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
//#include <iterator>
//#include <string>

#include "test_runner.h"

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
	auto p_size = prefix.size();
	auto low = lower_bound(range_begin, range_end, prefix, [p_size] (const string& s, const string& prefix) {return s.substr(0, p_size) < prefix;});
	auto up = upper_bound(range_begin, range_end, prefix, [p_size] (const string& prefix, const string& s) {return s.substr(0, p_size) > prefix;});
//	cout << *low << endl;
	return make_pair(low, up);
}

/*template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	auto low = lower_bound(range_begin, range_end, prefix, [] (const string& s, const char prefix) {return s[0] < prefix;});
	auto up = upper_bound(range_begin, range_end, prefix, [] (const char prefix, const string& s) {return s[0] > prefix;});
	return make_pair(low, up);
}*/

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}


int main() {

  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;

return 0;
}


//example
/*
*/
//#include <algorithm>
//#include <utility>
//#include <string>
//
//
//template <typename RandomIt>
//pair<RandomIt, RandomIt> FindStartsWith(
//	RandomIt range_begin, RandomIt range_end, string prefix) {
//
//  // Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
//  auto left = lower_bound(range_begin, range_end, prefix);
//
//  // Составим строку, которая в рамках буквенных строк является
//  // точной верхней гранью множества строк, начинающихся с prefix
//  string upper_bound = prefix;
//  ++upper_bound[upper_bound.size() - 1];
//
//  // Первое встреченное слово, не меньшее upper_bound,
//  // обязательно является концом полуинтервала
//  auto right = lower_bound(range_begin, range_end, upper_bound);
//
//  return {left, right};
//}
