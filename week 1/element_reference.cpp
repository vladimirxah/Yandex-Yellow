#include <iostream>
#include <vector>
#include <map>
#include <utility>
//#include <set>
//#include <iterator>
//#include <string>

using namespace std;

/*
 * Реализуйте шаблонную функцию GetRefStrict, которая на вход принимает: map и значение ключа k. Если элемент по ключу k в коллекции отсутствует, то функция должна бросить исключение runtime_error, иначе вернуть ссылку на элемент в коллекции.

Пример использования функции

map<int, string> m = {{0, "value"}};
string& item = GetRefStrict(m, 0);
item = "newvalue";
cout << m[0] << endl; // выведет newvalue
 *
 *
 *
 *
 */
template <typename Key, typename Val> Val& GetRefStrict(map<Key, Val>& m, const Key& k);

template <typename Key, typename Val> Val& GetRefStrict(map<Key, Val>& m, const Key& k) {
	Val* answer;
	try {
		answer = &(m.at(k));
	} catch (out_of_range&) {
		throw runtime_error("");
  }
	return *answer;
}





/*int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 1);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue

	return 0;
}*/


//example
/*
 *#include <map>
#include <stdexcept>

template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& input_map, KeyType key) {
    if (input_map.count(key) == 0) {
        throw runtime_error("no such key in dictionary");
    }
    return input_map[key];
}
 *
 * */
