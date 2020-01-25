/*
 * main.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 *
Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.

//vector<string> SplitIntoWords(const string& s);

Гарантируется, что:

строка непуста;
строка состоит лишь из латинских букв и пробелов;
первый и последний символы строки не являются пробелами;
строка не содержит двух пробелов подряд.

Подсказка
Рекомендуется следующий способ решения задачи:
искать очередной пробел с помощью алгоритма find;
создавать очередное слово с помощью конструктора строки по двум итераторам.

 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

//including course implementation
//#include "test_runner.h"

using namespace std;


/*template <typename T> void RemoveDuplicates(vector<T>& elements) {
	set<T> s(begin(elements), end(elements));
	elements.clear();
	copy(begin(s), end(s), back_inserter(elements));
}*/

template <typename DataType>
void RemoveDuplicates(vector<DataType>& elements) {
	sort(begin(elements), end(elements));
	unique(begin(elements), end(elements));
/*  elements.erase(
      unique(begin(elements), end(elements)),
      elements.end());*/
}

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}

int main() {

  vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    cout << x << " ";
  }
  cout << endl;

  vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const string& s : v2) {
    cout << s << " ";
  }
  cout << endl;

  return 0;
}


//example
/*Идея решения заключается в итеративном поиске очередного пробела в строке. Как только он найден, его позиция задаёт конец очередного слова, которое можно добавить к ответу. Поиск следующего пробела будет продолжаться со следующей позиции.
*/
//#include <algorithm>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//vector<string> SplitIntoWords(const string& str) {
//  // Готовим вектор, в который будем сохранять слова
//  vector<string> result;
//
//  // Эти два итератора будут ограничивать текущую не разбитую часть строки
//  // str_begin будет двигаться вправо
//  auto str_begin = begin(str);
//  // str_end всегда будет указывать на конец строки (поэтому он константный)
//  const auto str_end = end(str);
//
//  // У цикла нет условия завершения, так что единственный способ закончить его —
//  // сделать break
//  while (true) {
//
//    // Находим первый пробел в текущем «хвосте» строки
//    auto it = find(str_begin, str_end, ' ');
//
//    // Полуинтервал [str_begin, it) — очередное слово
//    result.push_back(string(str_begin, it));
//
//    if (it == str_end) {
//      // Если пробелов больше нет, цикл пора завершить.
//      // Последнее слово уже добавлено
//      break;
//    } else {
//      // Иначе первый символ после пробела — начало очередного слова.
//      // Туда и подвинем str_begin
//      str_begin = it + 1;
//    }
//
//  }
//
//  return result;
//}
