/*
 * inheritance.cpp
 *
 *  Created on: 26 апр. 2019 г.
 *      Author: goncharov
 */


#include <iostream>

using namespace std;

class Animal {
public:
	// ваш код
	Animal (const string& s) : Name(s) {

	}
	const string Name;
};


class Dog : public Animal {
public:
	// ваш код
	Dog (const string& s) : Animal(s) {

	}
	void Bark() {
			cout << Name << " barks: woof!" << endl;
	}
};

/*int main () {
//	Dog d("dog");
//	d.Bark();
	return 0;
}*/

//Example

/*#include <string>
#include <iostream>

using namespace std;

class Animal {
public:
  Animal(const string& name)
    : Name(name)
  {}

  const string Name;
};


class Dog : public Animal {
public:
  Dog(const string& name)
    : Animal(name)
  {}

  void Bark() {
        cout << Name << " barks: woof!" << endl;
  }
};*/
