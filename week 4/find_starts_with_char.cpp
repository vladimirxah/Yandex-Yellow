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

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
//#include <iterator>
//#include <string>

#include "test_runner.h"

using namespace std;
/*Сигнатура на обязана содержать const &, однако, функция не может изменять переданные объекты.
Тип Type1 должен быть таков, что объект типа T может быть неявно преобразован в Type1. Тип Type2 должен быть таков, что объект типа ForwardIt может быть разыменован и затем неявно преобразован в Type2. ​
bool cmp(const Type1 &a, const Type2 &b);*/
bool mygreater (const char& j, const string& s) { return (s[0] - 1) == j; }

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	auto low = lower_bound(range_begin, range_end, prefix, [] (const string& s, const char prefix) {return s[0] < prefix;});
	auto up = upper_bound(range_begin, range_end, prefix, [] (const char prefix, const string& s) {return s[0] > prefix;});
	return make_pair(low, up);
}

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}


int main() {

  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;

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
//    RandomIt range_begin, RandomIt range_end, char prefix) {
//      
//  // Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
//  auto left = lower_bound(range_begin, range_end, string(1, prefix));
//  
//  // Составим следующий в алфавите символ.
//  // Не страшно, если prefix = 'z':
//  // в этом случае мы получим следующий за 'z' символ в таблице символов
//  char next_prefix = static_cast<char>(prefix + 1);
//  
//  // Строка "<next_prefix>" в рамках буквенных строк
//  // является точной верхней гранью
//  // множества строк, начнающихся с '<prefix>'
//  auto right = lower_bound(range_begin, range_end, string(1, next_prefix));
//  
//  return {left, right};
//}
