/*
 * main.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 *
В этой задаче вам необходимо вычислить различные демографические показатели для группы людей. Человек представляется структурой Person:
	struct Person {
		int age;  // возраст
		Gender gender;  // пол
		bool is_employed;  // имеет ли работу
	};

Тип Gender определён следующим образом:
	enum class Gender {
		FEMALE,
		MALE
	};

Вам необходимо написать функцию PrintStats, получающую вектор людей, вычисляющую и выводящую медианный возраст для каждой из следующих групп людей:
все люди;
все женщины;
все мужчины;
все безработные женщины;
все занятые женщины;
все безработные мужчины;
все занятые мужчины.
Все 7 чисел нужно вывести в строгом соответствии с форматом (см. пример).

	void PrintStats(vector<Person> persons);

Принимая вектор по значению (а не по константной ссылке), вы получаете возможность модифицировать его копию произвольным образом и тем самым проще произвести вычисления.

Подсказка
Используйте алгоритм partition.

Вычисление медианного возраста
Для вычисления медианного возраста группы людей вы должны использовать функцию ComputeMedianAge:
	template <typename InputIt>
	int ComputeMedianAge(InputIt range_begin, InputIt range_end);

Эту функцию не нужно реализовывать самостоятельно: мы реализовали её за вас и автоматически добавим к каждому вашему решению.

Функцию ComputeMedianAge можно вызвать и для пустого набора людей: её результат в этом случае и нужно считать медианным возрастом пустого набора людей.

Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией функции PrintStats. Этот файл не должен содержать определения функции ComputeMedianAge и типов Person и Gender. В противном случае вы получите ошибку компиляции.

Гарантируется, что типы Person и Gender объявлены в точности так же, как в коде выше.

 */
#include <iostream>
#include <vector>
//#include <set>
#include <algorithm>
#include <numeric>
//#include <iterator>
#include <string>

//including course implementation
//#include "test_runner.h"

using namespace std;

enum class Gender;

struct Person {
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};

enum class Gender {
	FEMALE,
	MALE
};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

void PrintStats(vector<Person> persons) {
//	Median age = 40
	cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
//	Median age for females = 40
	auto gender_border = partition(begin(persons), end(persons), [] (const Person& curr) { return curr.gender == Gender::FEMALE; });
	cout << "Median age for females = " << ComputeMedianAge(begin(persons), gender_border) << endl;
//	Median age for males = 55
	cout << "Median age for males = " << ComputeMedianAge(gender_border, end(persons)) << endl;
//	Median age for employed females = 40
	auto employ_fem_border = partition(begin(persons), gender_border, [] (const Person& curr) { return curr.is_employed; });
	cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), employ_fem_border) << endl;
//	Median age for unemployed females = 80
	cout << "Median age for unemployed females = " << ComputeMedianAge(employ_fem_border, gender_border) << endl;
//	Median age for employed males = 55
	auto employ_men_border = partition(gender_border, end(persons), [] (const Person& curr) { return curr.is_employed; });
	cout << "Median age for employed males = " << ComputeMedianAge(gender_border, employ_men_border) << endl;
//	Median age for unemployed males = 78;
	cout << "Median age for unemployed males = " << ComputeMedianAge(employ_men_border, end(persons)) << endl;
}

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}


//EXAMPLE элегантнее. И там есть описание iota
int main() {

	vector<Person> persons = {
		{31, Gender::MALE, false},
		{40, Gender::FEMALE, true},
		{24, Gender::MALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};
	PrintStats(persons);

return 0;
}


//example
/*
Внимание! Ниже опубликовано решение необязательной задачи «Демографические показатели». Настоятельно рекомендуем попытаться её решить перед тем, как читать решение.
*/
//void PrintStats(vector<Person> persons) {
//    // Преобразуем порядок людей к следующему:
//    //                  persons
//    //                 /      \
//    //          females        males
//    //         /       \     /      \
//    //      empl.  unempl. empl.   unempl.
//    auto females_end = partition(
//        begin(persons), end(persons), [](const Person& p) {
//            return p.gender == Gender::FEMALE;
//        }
//    );
//    auto employed_females_end = partition(
//        begin(persons), females_end, [](const Person& p) {
//            return p.is_employed;
//        }
//    );
//    auto employed_males_end = partition(
//        females_end, end(persons), [](const Person& p) {
//            return p.is_employed;
//        }
//    );
//
//    // Теперь интересующие нас группы находятся в векторе непрерывно
//    cout << "Median age = "
//         << ComputeMedianAge(begin(persons), end(persons))          << endl;
//    cout << "Median age for females = "
//         << ComputeMedianAge(begin(persons), females_end)           << endl;
//    cout << "Median age for males = "
//         << ComputeMedianAge(females_end, end(persons))             << endl;
//    cout << "Median age for employed females = "
//         << ComputeMedianAge(begin(persons),  employed_females_end) << endl;
//    cout << "Median age for unemployed females = "
//         << ComputeMedianAge(employed_females_end, females_end)     << endl;
//    cout << "Median age for employed males = "
//         << ComputeMedianAge(females_end, employed_males_end)       << endl;
//    cout << "Median age for unemployed males = "
//         << ComputeMedianAge(employed_males_end, end(persons))      << endl;
//}
