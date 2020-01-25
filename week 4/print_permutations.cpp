/*
 * main.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 *
Дано целое положительное число N, не превышающее 9. Выведите все перестановки чисел от 1 до N в обратном лексикографическом порядке (см. пример).
 */
#include <iostream>
#include <vector>
//#include <set>
#include <algorithm>
//#include <iterator>
#include <string>

//including course implementation
//#include "test_runner.h"

using namespace std;


/*template <typename T> void RemoveDuplicates(vector<T>& elements) {
	set<T> s(begin(elements), end(elements));
	elements.clear();
	copy(begin(s), end(s), back_inserter(elements));
}*/

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}


//EXAMPLE элегантнее. И там есть описание iota
int main() {

	int target;
	cin >> target;
	string s;
	while (target > 0) {
		s.insert(begin(s), static_cast<char>(48 + target--));
	}
	vector<string> res;
  do {
		string tovec;
		for (auto sit = begin(s); sit < end(s); ++sit) {
			tovec.push_back(*sit);
			if (sit != (end(s) - 1)) tovec.push_back(' ');
		}
  	res.push_back(tovec);
	} while(std::next_permutation(s.begin(), s.end()));
  sort(rbegin(res), rend(res));
  for (auto it = begin(res); it < end(res); ++it) {
  	cout << *it << endl;
  }

return 0;
}


//example
/*Основная идея — использовать алгоритм prev_permutation для итеративного построения предыдущей перестановки по заданной. Его удобно обернуть в цикл do while.

Кроме того, для инициализации первой перестановки используем алгоритмы iota (заполняющий диапазон числами от 1 до n) и reverse.
*/
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <numeric>
//
//using namespace std;
//
//int main() {
//  int range_length;
//  cin >> range_length;
//  vector<int> permutation(range_length);
//
//  // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
//  // Заполняет диапазон последовательно возрастающими значениями
//  iota(permutation.begin(), permutation.end(), 1);
//
//  // reverse          -> http://ru.cppreference.com/w/cpp/algorithm/reverse
//  // Меняет порядок следования элементов в диапазоне на противоположный
//  reverse(permutation.begin(), permutation.end());
//
//  // prev_permutation ->
//  //     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
//  // Преобразует диапазон в предыдущую (лексикографически) перестановку,
//  // если она существует, и возвращает true,
//  // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
//  do {
//    for (int num : permutation) {
//      cout << num << ' ';
//    }
//    cout << endl;
//  } while (prev_permutation(permutation.begin(), permutation.end()));
//
//  return 0;
//}
