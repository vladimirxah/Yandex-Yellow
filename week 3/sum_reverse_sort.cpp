/*
 * sum_reverse_sort.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 */

/*
Вам дан заголовочный файл sum_reverse_sort.h, содержащий объявления трёх функций
Вам надо прислать cpp-файл, содержащий определения этих функций.
*/



#include <algorithm>
#include <string>
#include <vector>
#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	string rev;
	for (size_t i = s.size(); i > 0; --i) {
		rev.push_back(s[i - 1]);
	}
	return rev;
}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}


//EXAMPLE

/*
#include "sum_reverse_sort.h"

#include <algorithm>
using namespace std;

int Sum(int x, int y) {
  return x + y;
}

string Reverse(string s) {
  reverse(s.begin(), s.end());
  return s;
}

void Sort(vector<int>& nums) {
  sort(nums.begin(), nums.end());
}*/
