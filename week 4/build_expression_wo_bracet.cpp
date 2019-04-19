/*
 * main.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 *
Часть 1
Реализуйте построение арифметического выражения согласно следующей схеме:
*изначально есть выражение, состоящее из некоторого целого числа x;
*на каждом шаге к текущему выражению применяется некоторая операция: прибавление числа, вычитание числа, умножение на число или деление на число; перед применением операции выражение всегда должно быть заключено в скобки.
Пример

Формат ввода
В первой строке содержится исходное целое число x. Во второй строке содержится целое неотрицательное число N— количество операций. В каждой из следующих N строк содержится очередная операция:

прибавление числа a: + a;
либо вычитание числа b: - b;
либо умножение на число c: * c;
либо деление на число d: / d.
Количество операций может быть нулевым — в этом случае необходимо вывести исходное число.

Формат вывода
Выведите единственную строку — построенное арифметическое выражение.

Обратите внимание на расстановку пробелов вокруг символов:

каждый символ бинарной операции (+, -, * или /) должен быть окружён ровно одним пробелом с каждой стороны: (8) * 3;
символ унарного минуса (для отрицательных чисел) не нуждается в дополнительном пробеле: -5;
скобки и числа не нуждаются в дополнительных пробелах.
Подсказка
Для преобразования числа к строке используйте функцию to_string из библиотеки <string>.

Часть 2. Без лишних скобок
Модифицируйте решение предыдущей части так, чтобы предыдущее выражение обрамлялось скобками лишь при необходимости, то есть только в том случае, когда очередная операция имеет бо́льший приоритет, чем предыдущая.

8
5
* 3
- 6
/ 1
+ 5
* -2

8
2
+5
*2

-8
2
/5
*2



 */

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <iterator>
//#include <string>

#include "test_runner.h"

using namespace std;

enum class Operation {
	sum, ded, mul, div	//	+ - * /
};

struct next_member {
	next_member (char oper, int num) {
		member = num;
		switch (oper) {
		case '+':
			operat = Operation::sum;
			break;
		case '-':
			operat = Operation::ded;
			break;
		case '*':
			operat = Operation::mul;
			break;
		case '/':
			operat = Operation::div;
			break;
		}
	}

	string Make_String () const {
		string out;
		switch (operat) {
		case Operation::sum:
			out = " + ";
			out.append(to_string(member));
			break;
		case Operation::ded:
			out = " - ";
			out.append(to_string(member));
			break;
		case Operation::mul:
			out = " * ";
			out.append(to_string(member));
			break;
		case Operation::div:
			out = " / ";
			out.append(to_string(member));
			break;
		}
		return out;
	}
	Operation operat;
	int member;
};

ostream& operator << (ostream& os, const next_member& nm) {
	switch (nm.operat) {
	case Operation::sum:
		os << " + " << to_string(nm.member);
		break;
	case Operation::ded:
		os << " - " << to_string(nm.member);
		break;
	case Operation::mul:
		os << " * " << to_string(nm.member);
		break;
	case Operation::div:
		os << " / " << to_string(nm.member);
		break;
	}
	return os;
}

bool operator > (const next_member& lhs, const next_member& rhs) {
	int lhsi, rhsi;
	switch (lhs.operat) {
	case Operation::sum:
		lhsi = 1;
		break;
	case Operation::ded:
		lhsi = 1;
		break;
	case Operation::mul:
		lhsi = 2;
		break;
	case Operation::div:
		lhsi = 2;
		break;
	}
	switch (rhs.operat) {
	case Operation::sum:
		rhsi = 1;
		break;
	case Operation::ded:
		rhsi = 1;
		break;
	case Operation::mul:
		rhsi = 2;
		break;
	case Operation::div:
		rhsi = 2;
		break;
	}
	return lhsi > rhsi;
}

string Print_Exp (string& sfm, const int& fm, const vector<next_member> nm) {
//	fm >= 0 ? sfm.append(to_string(fm)) : sfm.append("(" + to_string(fm) + ")");
	sfm.append(to_string(fm));
	for (auto it = begin(nm); it < end(nm); ++it) {
		if (it == begin(nm)) sfm.append((*it).Make_String());
		if (*it > *(it - 1) && it != begin(nm)) {
			sfm = "(" + sfm + ")";
			sfm.append((*it).Make_String());
		} else if (it != begin(nm)) {
			sfm.append((*it).Make_String());
		}

	}
	return sfm;
}

void TestWorks() {
//	AssertEqual(PrintVectorPart({6, 1, 8, -5, 4}), "8 1 6", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({-6, 1, 8, -5, 4}), "", "Just to check that Assert works");
//	AssertEqual(PrintVectorPart({6, 1, 8, 5, 4}), "4 5 8 1 6", "Just to check that Assert works");
}


int main() {
	int q, fm;
	string sfm;
	vector<next_member> expression_vec;
	cin >> fm >> q;
	if (q != 0) {
		for (auto i = 0; i < q; ++i) {
			char oper;
			int num;
			cin >> oper >> num;
			expression_vec.push_back({oper, num});
		}
		Print_Exp(sfm, fm, expression_vec);
	}
	q == 0 ? cout << fm << "\n" : cout << sfm << "\n";

return 0;
}


//example
/*
*/
//#include <algorithm>
//#include <utility>
//#include <string>
//
//
//template <typename RandomIt>
//pair<RandomIt, RandomIt> FindStartsWith(
//    RandomIt range_begin, RandomIt range_end, char prefix) {
//
//  // Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
//  auto left = lower_bound(range_begin, range_end, string(1, prefix));
//
//  // Составим следующий в алфавите символ.
//  // Не страшно, если prefix = 'z':
//  // в этом случае мы получим следующий за 'z' символ в таблице символов
//  char next_prefix = static_cast<char>(prefix + 1);
//
//  // Строка "<next_prefix>" в рамках буквенных строк
//  // является точной верхней гранью
//  // множества строк, начнающихся с '<prefix>'
//  auto right = lower_bound(range_begin, range_end, string(1, next_prefix));
//
//  return {left, right};
//}
