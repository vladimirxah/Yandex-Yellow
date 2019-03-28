#include <iostream>
#include <vector>
#include <map>
#include <utility>
//#include <set>
//#include <iterator>
//#include <string>

using namespace std;

/*
 * Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров. Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:

для vector элементы нужно возвести в квадрат;
для map в квадрат нужно возвести только значения, но не ключи;
для pair в квадрат нужно возвести каждый элемент пары.
// Пример вызова функции
vector<int> v = {1, 2, 3};
cout << "vector:";
for (int x : Sqr(v)) {
  cout << ' ' << x;
}
cout << endl;
map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
};
cout << "map of pairs:" << endl;
for (const auto& x : Sqr(map_of_pairs)) {
  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
}
//Код выше должен вывести
vector: 1 4 9
map of pairs:
4 4 4
7 16 9

Функция должна корректно работать не только для контейнеров, состоящих из чисел, но и для составных объектов, например, векторов словарей пар чисел.

Для успешной сдачи решения необходимо сделать предварительное объявление шаблонных функций перед всеми шаблонными функциями.

Пример предварительного объявления шаблонной функции
// Предварительное объявление шаблонных функций
template<typename T> T FuncA(T x);
template<typename T> void FuncB(T x);

// Объявляем шаблонные функции
template <typename T>
T FuncA(T x) { /.../ }

template <typename T>
void FuncB(T x) { /.../ }
 *
 *
 *
 *
 */

template <typename T> T Sqr(const T& x);
template <typename T> vector<T> Sqr(const vector<T>& x);
template <typename Key, typename Val> map<Key, Val> Sqr(const map<Key, Val>& m);
template <typename First , typename Second > pair <First , Second > Sqr(const pair <First , Second >& p1);

// функция квадрата для чисел
template <typename T>
T Sqr(const T& t) {
	T a = t * t;
	return a;
}

// функция квадрата для векторов
template <typename T>
vector<T> Sqr(const vector<T>& v) {
	vector<T> va;
	for (const T& i : v) {
		va.push_back(Sqr(i));
	}
	return va;
}

// функция квадрата для словаря
template <typename Key, typename Val>
map<Key, Val> Sqr(const map<Key, Val>& m) {
	map<Key, Val> ma;
	for (const pair<Key, Val>& i : m) {
		ma.emplace(i.first, Sqr(i.second));
	}
	return ma;
}

// функция квадрата для пары
template <typename First , typename Second >
pair <First , Second > Sqr (const pair <First , Second >& p1) {
First f = Sqr(p1.first);
Second s = Sqr(p1.second);
return {f, s};
}
