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
//#include <iterator>
#include <string>

//including course implementation
//#include "test_runner.h"

using namespace std;

//объявление шаблонов
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);
template <typename RandomIt>
void Merge(RandomIt lh_begin, RandomIt lh_end, RandomIt rh_begin, RandomIt rh_end, RandomIt range_begin, RandomIt range_end);

//шаблон для сортировки слиянием при разбиении на 2 части
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
//	выходим из функции, если 0 или 1 элемент
	if ((range_end - range_begin) < 2) {
		return;
	}
//	создаем временный вектор с копией элементов
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
//	определяем середину временного вектора
	typename std::vector<typename RandomIt::value_type>::iterator middle = elements.begin() + (elements.end() - elements.begin()) / 2;
//	сортируем обе половины
	MergeSort(begin(elements), middle);
	MergeSort(middle, end(elements));
//	сливаем половины временного вектора на место основного вектора
	Merge(begin(elements), middle, middle, end(elements), range_begin, range_end);
}

template <typename RandomIt>
void Merge(RandomIt lh_begin, RandomIt lh_end, RandomIt rh_begin, RandomIt rh_end, RandomIt range_begin, RandomIt range_end) {
//	пока не прошли по всему основному вектору (т.е. пока указатель начала не равен указателю конца)
	while (range_begin != range_end) {
//		пока оба отсортированных временных векторов содержат элементы, сравниваем их и пишем в основной вектор (не забывая перемещать указатели вперед)
		if (lh_begin != lh_end && rh_begin != rh_end) {
			*rh_begin < *lh_begin ? *(range_begin++) = *(rh_begin++) : *(range_begin++) = *(lh_begin++);
//		берем только из левого вектора, если правый пуст
		} else if (lh_begin != lh_end) {
			*(range_begin++) = *(lh_begin++);
//		берем только из правого вектора, если левый пуст
		} else {
			*(range_begin++) = *(rh_begin++);
		}
	}
}


void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}


int main() {

	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;

return 0;
}


//example
/*
В этой задаче достаточно аккуратно реализовать предложенный алгоритм, не ошибившись при использовании итераторов.
*/
/*Часть 1. Разбиение на 2 части
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
  int range_length = range_end - range_begin;
  if (range_length < 2) {
    return;
  }

  // 2. Создаем вектор, содержащий все элементы текущего диапазона
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  // 3. Разбиваем вектор на две равные части
  auto mid = elements.begin() + range_length / 2;

  // 4. Вызываем функцию MergeSort от каждой половины вектора
  MergeSort(elements.begin(), mid);
  MergeSort(mid, elements.end());

  // 5. С помощью алгоритма merge сливаем отсортированные половины
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  merge(elements.begin(), mid, mid, elements.end(), range_begin);
}

Часть 2. Разбиение на 3 части
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
  int range_length = range_end - range_begin;
  if (range_length < 2) {
    return;
  }

  // 2. Создаем вектор, содержащий все элементы текущего диапазона
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  // 3. Разбиваем вектор на три равные части
  auto one_third = elements.begin() + range_length / 3;
  auto two_third = elements.begin() + range_length * 2 / 3;

  // 4. Вызываем функцию MergeSort от каждой трети вектора
  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());

  // 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
  // back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
  vector<typename RandomIt::value_type> interim_result;
  merge(elements.begin(), one_third, one_third, two_third,
        back_inserter(interim_result));

  // 6. С помощью алгоритма merge сливаем отсортированные части
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  merge(interim_result.begin(), interim_result.end(), two_third, elements.end(),
        range_begin);
}*/
