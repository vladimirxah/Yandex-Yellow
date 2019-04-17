/*
 * main.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 *
Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного типа RandomIt и сортирующую заданный ими диапазон с помощью сортировки слиянием. Гарантируется, что:

* итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки, то есть их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
* сортируемые объекты можно сравнивать с помощью оператора <.
	template <typename RandomIt>
	void MergeSort(RandomIt range_begin, RandomIt range_end);

Часть 1. Реализация с разбиением на 2 части
Алгоритм
Классический алгоритм сортировки слиянием выглядит следующим образом:

Если диапазон содержит меньше 2 элементов, выйти из функции.
Создать вектор, содержащий все элементы текущего диапазона.
Разбить вектор на две равные части. (В этой задаче гарантируется, что длина передаваемого диапазона является степенью двойки, так что вектор всегда можно разбить на две равные части.)
Вызвать функцию MergeSort от каждой половины вектора.
С помощью алгоритма merge слить отсортированные половины, записав полученный отсортированный диапазон вместо исходного.
Вы должны реализовать именно этот алгоритм и никакой другой: тестирующая система будет проверять, что вы выполняете с элементами именно эти действия.

Подсказка
Чтобы создать вектор, содержащий все элементы текущего диапазона (п. 2 алгоритма), необходимо уметь по типу итератора узнавать тип элементов, на которые он указывает. Если итератор RandomIt принадлежит стандартному контейнеру (вектору, строке, множеству, словарю...), нижележащий тип можно получить с помощью выражения typename RandomIt::value_type. Таким образом, гарантируется, что создать вектор в п. 2 можно следующим образом:
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

		Пример кода
		int main() {
			vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
			MergeSort(begin(v), end(v));
			for (int x : v) {
				cout << x << " ";
			}
			cout << endl;
			return 0;
		}

		Вывод
		0 1 4 4 4 6 6 7

Часть 2. Реализация с разбиением на 3 части
Реализуйте сортировку слиянием, разбивая диапазон на 3 равные части, а не на 2. Гарантируется, что длина исходного диапазона является степенью 3.

Соответственно, пункты 3–5 алгоритма нужно заменить следующими:

Разбить вектор на 3 равные части.
Вызвать функцию MergeSort от каждой части вектора.
Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, записав полученный отсортированный диапазон вместо исходного.

		Пример кода
		int main() {
			vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
			MergeSort(begin(v), end(v));
			for (int x : v) {
				cout << x << " ";
			}
			cout << endl;
			return 0;
		}

		Вывод
		0 1 4 4 4 5 6 6 7
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

#include "test_runner.h"

using namespace std;

//объявление шаблонов
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);
template <typename RandomIt, typename T>
void Merge(vector<T>& elements, RandomIt middle_left, RandomIt middle_right, RandomIt range_begin, RandomIt range_end, bool first_call);

template <typename RandomIt>
void PrintArray(RandomIt range_begin, RandomIt range_end) {
	for (auto it = range_begin; it < range_end; ++it) {;
	cout << *it << " ";
	}
	cout << endl;
}

//шаблон для сортировки слиянием при разбиении на 2 части
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
//	выходим из функции, если 0 или 1 элемент
	if ((range_end - range_begin) < 2) {
		return;
	}
//	создаем временный вектор с копией элементов
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
//	Разбить вектор на 3 равные части.
	typename std::vector<typename RandomIt::value_type>::iterator middle_left = elements.begin() + (elements.end() - elements.begin()) / 3;
	typename std::vector<typename RandomIt::value_type>::iterator middle_right = elements.begin() + (elements.end() - elements.begin()) / 3 * 2;
//	Вызвать функцию MergeSort от каждой части вектора.
	MergeSort(begin(elements), middle_left);
	MergeSort(middle_left, middle_right);
	MergeSort(middle_right, end(elements));
			cout << "1/3: ";
			PrintArray(begin(elements), middle_left);
			cout << "2/3: ";
			PrintArray(middle_left, middle_right);
			cout << "3/3: ";
			PrintArray(middle_right, end(elements));
//	Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
	Merge(elements, middle_left, middle_right, range_begin, range_end, true);
			cout << "After merge 1/3 + 2/3:\t";
			PrintArray(begin(elements), middle_right);
			cout << "\t\t3/3:\t";
			PrintArray(middle_right, end(elements));
//	Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, записав полученный отсортированный диапазон вместо исходного.
	Merge(elements, middle_left, middle_right, range_begin, range_end, false);
			cout << "After merge 1-2/3 + 3/3:\t";
			PrintArray(range_begin, range_end);
}

template <typename RandomIt, typename T>
void Merge(vector<T>& elements, RandomIt middle_left, RandomIt middle_right, RandomIt range_begin, RandomIt range_end, bool first_call) {
	if (first_call) {
//		создаем указатели для первых двух третей вектора
/*		typename vector<T>::iterator lp = elements.begin();
		typename vector<T>::iterator rp = middle_left;*/
//		Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
				cout << "first look at elements - ";
				PrintArray(elements.begin(), elements.end());
//				PrintArray(range_begin, range_end);
				cout << "lh - ";
				PrintArray(elements.begin(), middle_left);
				cout << "rh - ";
				PrintArray(middle_left, middle_right);
		merge(elements.begin(), middle_left, middle_left, middle_right, back_inserter(elements));
				cout << "temp vector must be biger - ";
				PrintArray(elements.begin(), elements.end());
	} else {
//		Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, записав полученный отсортированный диапазон вместо исходного.
		//	пока не прошли по всему основному вектору (т.е. пока указатель начала не равен указателю конца)
		while (range_begin != range_end) {
			typename std::vector<T>::iterator lp = middle_right;
			int end_of_old_el = (middle_left - elements.begin()) / 2 * 3;
			typename std::vector<T>::iterator rp = middle_right + end_of_old_el;

			while (lp != (middle_right + end_of_old_el) && rp != elements.end()) {
				*rp < *lp ? *(range_begin++) = *(rp++) : *(range_begin++) = *(lp++);
			}
			if (lp != middle_left) {
				*(range_begin++) = *(lp++);
			} else {
				*(range_begin++) = *(rp++);
			}

/*		//		пока оба отсортированных временных векторов содержат элементы, сравниваем их и пишем в основной вектор (не забывая перемещать указатели вперед)
			if (lh_begin != lh_end && rh_begin != rh_end) {
				*rh_begin < *lh_begin ? *(range_begin++) = *(rh_begin++) : *(range_begin++) = *(lh_begin++);
		//		берем только из левого вектора, если правый пуст
			} else if (lh_begin != lh_end) {
					*(range_begin++) = *(lh_begin++);
		//		берем только из правого вектора, если левый пуст
			} else {
				*(range_begin++) = *(rh_begin++);
			}*/
		}
	}


}


void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}


int main() {

	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;

return 0;
}


//example
/*
Внимание! Ниже опубликовано решение необязательной задачи «Демографические показатели». Настоятельно рекомендуем попытаться её решить перед тем, как читать решение.
*/

