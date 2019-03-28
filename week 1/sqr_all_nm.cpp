#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

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


//Образец

/*// Объявим функции без тела,
// чтобы их можно было использовать в произвольном порядке

// Для простых типов
template<typename T>
T Sqr(T value);

// Для вектора
template<typename T>
vector<T> Sqr(const vector<T>& value);

// Для словаря
template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value);

// Для пары
template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value);

// Теперь реализуем их в соответствии с заданием
template<typename T>
T Sqr(T value) {
  return value * value;
}

template<typename T>
vector<T> Sqr(const vector<T>& value) {
  vector<T> result;
  for (const T& x : value) {
    // Здесь важно, что вместо x * x вызывается функция Sqr:
    // это позволяет возводить в квадрат составные объекты
    result.push_back(Sqr(x));
  }

  return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value) {
  map<K, V> result;
  for (const auto& element : value) {
    result[element.first] = Sqr(element.second);
  }
  return result;
}

template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value) {
  return {Sqr(value.first), Sqr(value.second)};
}*/
