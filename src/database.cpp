/*
 * database.cpp
 *
 *  Created on: 11 февр. 2020 г.
 *      Author: gonchrov
 */

#include "database.h"

void Database::Add (const Date& date, const string& event) {
	/*Команда Add
	Встретив команду Add date event, ваша программа должна добавить пару (date, event) в базу данных и затем показывать её при поиске (команда Find) или печати (команда Print). Одинаковые события, произошедшие в один и тот же день, сохранять не нужно: добавление в базу уже существующей пары (date, event) должно игнорироваться. В одну и ту же дату может произойти много разных событий, БД должна суметь их все сохранить.
	Гарантируется, что поле date в команде Add имеет формат «Год-Месяц-День», где Год — это целое число от 0 до 9999, Месяц — это номер месяца от 1 до 12 включительно, День — это номер дня от 1 до 31 включительно. После даты обязательно следует пробел, отделяющий её от события. Примеры корректных дат: 2017-11-07, 0-2-31.
	Вся остальная часть строки в команде Add задаёт событие. Оно может содержать пробелы, поэтому для его считывания удобно воспользоваться функцией getline. При этом гарантируется, что название события не может содержать символ кавычки ("). Таким образом, этот символ может встретиться лишь в условии в командах Find и Del, являясь ограничителем названия события.*/
	pair<set<string>::iterator,bool> ret; //для сохранения результата вставки в set
	set<string> &ss = db_set_[date]; // ссылка на set для этой даты
	ret = ss.insert(event); //попытка вставки
	if (ret.second) {
		db_vec_[date].push_back(event); //добавление события в вектор БД, если события ранее не было (проверяю через добавление в set
	}
}

ostream& Database::Print (ostream& os) const {
	/*Встретив команду Print, ваша программа должна вывести все пары (дата, событие), которые в данный момент содержатся в базе данных. Пары надо выводить по одной в строке. Они должны быть отсортированы по дате по возрастанию. События в рамках одной даты необходимо выводить в порядке добавления (за исключением уже удалённых и попыток добавления повторов).

	Даты надо выводить в формате ГГГГ-ММ-ДД, где Г, М, Д — это цифры чисел года, месяца и дня соответственно. Если какое-то число имеет меньше разрядов, чем нужно, его надо дополнить нулями, например: 0001-01-01 — первое января первого года.*/
	for (auto it = db_vec_.begin(); it != db_vec_.end(); ++it) {
		auto &val_vector = it->second;
		for (auto it_v = val_vector.begin(); it_v != val_vector.end(); ++it_v) {
			os << it->first << " ";
			os << *it_v << endl;
		}
	}
	return os;
}

int Database::RemoveIf (function<bool(const Date& date, const string& event)> predicate) {
	map<Date, set<string>> temp_set;
	map<Date, vector<string>> temp_vec;
	int count_del = 0;
	//прохожу итератором по базе с множествами сравнивая каждую пару год и событие функцией predicate. Если они подходят
	//под заданное условие - добавляю их во временную БД, чтобы их потом можно было вычесть
	for (auto it_m = db_set_.begin(); it_m != db_set_.end(); ++it_m) {
		auto &val_set = it_m->second;
		for (auto it_s = val_set.begin(); it_s != val_set.end(); ++it_s) {
			auto &date = it_m->first;
			auto& event = it_s;
			if (predicate(date, *event)) {
				++count_del;
				temp_set[date].insert(*event);
//				temp_vec[date].push_back(*event);
			}
		}
	}
	//если были удаления из базы, надо пройтись по базе и удалить ненужные события
	if (count_del > 0) {
		for (auto it_m = db_set_.begin(); it_m != db_set_.end(); ++it_m) {
			auto &date = it_m->first;
			if (temp_set.find(date) != temp_set.end()) {
				set<string> set_dif;
				auto &val_set = it_m->second;
				set_difference(val_set.begin(), val_set.end(), temp_set[date].begin(), temp_set[date].end(),
						std::inserter(set_dif, set_dif.end()));
				db_set_[date] = set_dif;
			}

		}
		set<string> set_dif;

	}
	return count_del;
//	condition->Evaluate()
}

vector<record> Database::FindIf (function<bool(const Date& date, const string& event)> predicate) const {
	vector<record> founded_events;
	for (auto it_m = db_vec_.begin(); it_m != db_vec_.end(); ++it_m) {
		auto &val_vec = it_m->second;
		for (auto it_v = val_vec.begin(); it_v != val_vec.end(); ++it_v) {
			if (predicate(it_m->first, *it_v)) {
				founded_events.push_back(make_pair(it_m->first, *it_v));
			}
		}
	}
	return founded_events;
}

string Database::Last(const Date& date) const {
/*	По команде Last date нужно вывести последнее из событий, случившихся к дате date. Более формально:
	среди всех имеющихся дат событий нужно найти наибольшую, не превосходящую date;
	из всех событий с такой датой нужно выбрать последнее добавленное и вывести в формате, аналогичном формату команды Print;
	если date меньше всех имеющихся дат, необходимо вывести «No entries».*/
	const auto it_founded = upper_bound(begin(db_vec_), end(db_vec_), date);
//	const auto it_founded = db_vec_.lower_bound(date);
	if (it_founded == db_vec_.end()) {
		return "No entries";
	} else {
		stringstream ss;
		ss << it_founded->first << " " << it_founded->second.back();
		return ss.str();
	}
	/*try {
		const vector<string> &vec = db_vec_.at(date);
		return make_pair(date,vec.back());
	}	catch (const exception& e) {
    cout << e.what() << endl;
  }*/
//	return make_pair(date, "ERROR, NO LAST EVENT AT THIS DATE");		//добавил, чтобы не было Warning
}

unsigned int Database::Size() const {
	return db_vec_.size();
}

ostream& operator<<(ostream& stream, const record& rec) {
	stream << rec.first << ' ' << rec.second;
  return stream;
}

//i cant use
bool operator<(const Date& lhs, const pair<Date, vector<string>>& rhs) {
	return lhs < rhs.first;
}
