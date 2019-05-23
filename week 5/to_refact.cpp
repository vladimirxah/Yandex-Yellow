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
	virtual void Walk (string destination) const = 0;
	string Type () const {
		return Type_;
	}
	string Name () const {
		return Name_;
	}
private:
	string Type_;
	string Name_;
};

class Student : public Human {
public:

    Student(const string& name, const string& favouriteSong) : Human("Student", name), Type_("Student"), Name_(name), FavouriteSong(favouriteSong) {}

    void Learn() {
        cout << Type_ << ": " << Name_ << " learns" << endl;
    }

    void Walk(string destination) const override{
        cout << Type_ << ": " << Name_ << " walks to: " << destination << endl;
        cout << Type_ << ": " << Name_ << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << Type_ << ": " << Name_ << " sings a song: " << FavouriteSong << endl;
    }

private:
    string Type_;
    string Name_;
    string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human("Teacher",name), Type_("Teacher"), Name_(name), Subject(subject) {}

    void Teach() {
        cout << Type_ << ": " << Name_ << " teaches: " << Subject << endl;
    }

    void Walk(string destination) const override {
        cout << Type_ << ": " << Name_ << " walks to: " << destination << endl;
    }

private:
    const string Type_;
    string Name_;
    string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human("Policeman", name), Type_("Policeman"), Name_(name) {}

    void Check(const Human& h) const {
    		cout << Type_ << ": " << Name_ << " checks " << h.Type() << ". " << h.Type() << "'s name is: " << h.Name() << endl;
    }

    void Walk(string destination) const override {
        cout << Type_ << ": " << Name_ << " walks to: " << destination << endl;
    }

private:
    const string Type_;
    string Name_;
};

void VisitPlaces(const Human& h, vector<string> places) {
    for (auto p : places) {
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
