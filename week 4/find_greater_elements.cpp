/*
 * main.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 *
Напишите шаблонную функцию FindGreaterElements, принимающую множество elements объектов типа T и ещё один объект border типа T и возвращающую вектор из всех элементов множества, бо́льших border, в возрастающем порядке.
 */
#include <iostream>
#include <vector>
#include <set>

#include "..\src\test_runner.h"

using namespace std;

template <typename T> vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
	vector<T> v;
	for (auto it = begin(elements); it != end(elements); ++it) {
		if (*it > border) {
			v.push_back(*it);
		}
	}
	return v;
}

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}

int main() {

	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;

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
