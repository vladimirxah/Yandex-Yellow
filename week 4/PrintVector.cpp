/*
 * PrintVector.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 */

#include "PrintVector.h"

/*ostream& operator << (ostream& os, vector<int>& v) {
	for (auto i : v) {
		os << i << " ";
	}
	return os;
}*/

void PrintVectorPart(const vector<int>& numbers) {
	auto it = find_if(numbers.begin(), numbers.end(), [] (const auto& s) { return s < 0; } );
	if (it == numbers.end()) {
		while (it != numbers.begin()) {
			--it;
			cout << *it << " ";
		}
	} else {
		while (it != numbers.begin()) {
			--it;
			cout << *it << " ";
		}
	}
}



//Example
/*
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
  auto negative_it = find_if(
    numbers.begin(), numbers.end(),
    [](int number) {
      return number < 0;
    }
  );

  for (auto it = negative_it; it != numbers.begin(); ) {
    cout << *(--it) << " ";
  }
}*/
