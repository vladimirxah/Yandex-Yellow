/*
 * to_refact.cpp
 *
 *  Created on: 13 мая 2019 г.
 *      Author: goncharov
 */

/*В данном задании вам предстоит изменить код таким образом, чтобы он соответствовал изложенным в курсе принципам.

Представьте, что этот код вам достался в наследство от коллеги и теперь вам предстоит поддерживать его и улучшать. Первое, что вы решили сделать — это провести рефакторинг.

Конечные цели рефакторинга:

упростить дальнейшую поддержку кода;
уменьшить сложность кода;
упростить добавление новых абстракций в программу.*/

/*Задание будет оцениваться по следующим критериям:

эффективность выполнения кода;
задублированность кода;
эффективность использования приёмов рефакторинга кода, показанных в лекциях.
Кроме того, присылаемый вами код должен компилироваться.*/


#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Human {
public:
	Human (const string& Type, const string& Name) : Type_(Type), Name_(Name) {}
	virtual ~Human () {}
	virtual void Walk (const string& destination) const = 0;
	string Type () const {
		return Type_;
	}
	string Name () const {
		return Name_;
	}
	string Log () const {
		return Type() + ": " + Name();
	}
private:
	const string Type_;
	const string Name_;
};

class Student : public Human {
public:

    Student(const string& name, const string& favouriteSong) : Human("Student", name), FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << Log() << " learns" << endl;
    }

    void Walk(const string& destination) const override{
        cout << Log() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << Log() << " sings a song: " << FavouriteSong << endl;
    }

private:
    string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human("Teacher",name), Subject(subject) {}

    void Teach() const {
        cout << Log() << " teaches: " << Subject << endl;
    }

    void Walk(const string& destination) const override {
        cout << Log() << " walks to: " << destination << endl;
    }

private:
    string Subject;
};

class Policeman : public Human {
public:
    Policeman(const string& name) : Human("Policeman", name) {}

    void Check(const Human& h) const {
    		cout << Log() << " checks " << h.Type() << ". " << h.Type() << "'s name is: " << h.Name() << endl;
    }

    void Walk(const string& destination) const override {
        cout << Log() << " walks to: " << destination << endl;
    }

};

void VisitPlaces(const Human& h, const vector<string>& places) {
    for (const auto& p : places) {
			h.Walk(p);
    }
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, {"Moscow", "London"});
	p.Check(s);
	VisitPlaces(s, {"Moscow", "London"});
	return 0;
}
