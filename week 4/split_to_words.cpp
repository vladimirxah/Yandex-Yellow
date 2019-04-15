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

#include "test_runner.h"

using namespace std;

//пока что не выводит последнее слово
vector<string> SplitIntoWords(const string& s) {
	vector<string> v = {};
	string k;
	int c = 0;
	auto beg = s.begin();
	auto it = find(beg, s.end(), ' ');
	while (it != end(s) && c != 9) {
		k = {beg, it};
		v.push_back(k);
		beg = it + 1;
		it = find(beg, end(s), ' ');
		c++;
	}
	return v;
}

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}

int main() {

  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}


//example
/*Ключевой момент решения — поиск первого элемента, большего border. Позже мы научимся делать это оптимально, а пока достаточно использовать для этого обычный цикл while.

Как только найден итератор на первый элемент, больший border, достаточно создать вектор из полуинтервала, начинающегося в этом итераторе и заканчивающегося в конце множества — это и будут все элементы, большие border, в возрастающем порядке.*/
//#include <iostream>
//#include <set>
//#include <vector>
//
//using namespace std;
//
//template <typename T>
//vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
//  // Начнём итерироваться по множеству
//  auto it = begin(elements);
//  // Цель — найти первый элемент, больший border
//  // Если итератор не достиг конца и указывает не туда, двигаем
//  while (it != end(elements) && *it <= border) {
//  	++it;
//  }
//  // Возвращаем вектор, созданный из элементов множества, начиная с it
//  return {it, end(elements)};
//}
