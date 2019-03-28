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

template <typename T> T Sqr(T x);
template <typename T> vector<T> Sqr(vector<T> x);
template <typename Key, typename Val> map<Key, Val> Sqr(const map<Key, Val>& m);
template <typename First , typename Second > pair <First , Second > Sqr (const pair <First , Second >& p1);
template <typename T> vector<T> operator* (const vector<T>& v);

// оператор умножения для пары
template <typename First , typename Second >
pair <First , Second > operator * (const pair <First , Second >& p1 ,
const pair <First , Second >& p2) {
First f = p1.first * p2.first;
Second s = p1.second * p2.second;
return {f, s};
}

// оператор умножения для векторов
template <typename V>
std::vector<V> operator* (const std::vector<V>& v) {
	vector<V> va;
	for (V& i : v) {
		va.push_back(i * i);
	}
	return va;
}

// оператор умножения для векторов словарей
template <typename MK, typename MV>
std::vector<map<MK, MV>> operator* (const std::vector<map<MK, MV>>& v) {
	vector<map<MK, MV>> va;
	for (map<MK, MV>& i : v) {
		va.push_back(i * i);
	}
	return va;
}

// оператор умножения для словаря
template <typename Key, typename Val>
map<Key, Val> operator* (const map<Key, Val>& m1, const map<Key, Val>& m2) {
	map<Key, Val> ma;
	for (const pair<Key, Val>& i : m1) {
		ma[i.first] = m1.at(i.first) * m2.at(i.first);
	}
	return ma;
}

// функция квадрата для чисел
template <typename T>
T Sqr(const T& t) {
	return t * t;
}

// функция квадрата для векторов
template <typename T>
vector<T> Sqr(const vector<T>& v) {
	vector<T> va;
	for (const T& i : v) {
		va.push_back(i * i);
	}
	return va;
}

// функция квадрата для словаря
template <typename Key, typename Val>
map<Key, Val> Sqr(const map<Key, Val>& m) {
	map<Key, Val> ma;
	for (const pair<Key, Val>& i : m) {
		ma[i.first] = Sqr(i.second);
	}
	return ma;
}

// функция квадрата для пары
template <typename First , typename Second >
pair <First , Second > Sqr (const pair <First , Second >& p1) {
First f = p1.first * p1.first;
Second s = p1.second * p1.second;
return {f, s};
}




int main() {
	// Квадрат векотра
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
	vector<int> v2 = { 1, 2, 3 };
	vector<int> v1{ 4,5,6 };
	map<vector<int>, vector<int>> Map_vector{
		{v2,v1},	{v1,v2}
	};
	for (auto& item : Sqr(Map_vector)) {
		for (auto& v : item.second) {
			cout << v << ' ';
		}
		cout << '\n';
	}
/*	map<int, pair<int, int>> map_of_pairs2 = {
		  {5, {3, 3}},
		  {8, {5, 4}}
		};
	vector<map<int, pair<int, int>>> vm = {map_of_pairs, map_of_pairs2};
	for (int x : Sqr(vm)) {
		cout << ' ' << x;
	}*/

	return 0;
}



/*
 *
 * */
