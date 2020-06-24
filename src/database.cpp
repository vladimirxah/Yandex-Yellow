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
	/*удалить из базы все записи, которые удовлетворяют условию condition
	 Встретив команду Del condition, ваша программа должна удалить из базы данных все события, удовлетворяющие условию condition, и вывести в стандартный вывод количество удалённых записей N в формате «Removed N entries». Если условие пусто, результатом выполнения команды должна стать очистка всей базы данных*/

	map<Date, set<string>> new_map_set;		//Словарь дат в множество событий. Заношу сюда не удаляемые события.
	map<Date, vector<string>> new_map_vec;		//Словарь дат в вектор событий. Заношу сюда не удаляемые события.
	int count_del = 0;		//все равно надо выводить количество удаленных событий
	//прохожу итератором по базе с векторами дат-событий сравнивая каждую пару год и событие функцией predicate. Если они подходят
	//под заданное условие - добавляю их во временную БД c вектором, чтобы их потом можно было заменить базе множеств и векторов
	for (auto it_m = db_vec_.begin(); it_m != db_vec_.end(); ++it_m) {
		auto date = it_m->first;
		auto &val_vec = it_m->second;
		for (auto it_s = val_vec.begin(); it_s != val_vec.end(); ++it_s) {
			if (!predicate(date, *it_s)) {
				new_map_set[date].insert(*it_s);
				new_map_vec[date].push_back(*it_s);
			} else {
				++count_del;
			}
		}
	}
	if (count_del > 0) {
		db_vec_ = new_map_vec;
		db_set_ = new_map_set;
	}
	return count_del;
}

vector<string> Database::FindIf (function<bool(const Date& date, const string& event)> predicate) const {
	vector<string> founded_events;
	for (auto it_m = db_vec_.begin(); it_m != db_vec_.end(); ++it_m) {
		auto &val_vec = it_m->second;
		for (auto it_v = val_vec.begin(); it_v != val_vec.end(); ++it_v) {
			if (predicate(it_m->first, *it_v)) {
				founded_events.push_back(it_m->first.Str() + " " + *it_v);
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

	if (db_vec_.empty()) {
		return "No entries";
	}
	auto it = db_vec_.upper_bound(date);
	if (it == db_vec_.begin()) {
		return "No entries";		//Upperbound equals begin of vector
	} else {
		it--;
		if (!it->second.empty()) {
			stringstream ss;
			ss << it->first << " " << it->second.back();
			return ss.str();
		}
		else {
			throw invalid_argument("Vector for this Date is Empty");
		}
	}
}

unsigned int Database::Size() const {
	auto vec_size = db_vec_.size();
	auto set_size = db_set_.size();
	if ( vec_size == set_size ) {
		return vec_size;
	} else {
		throw runtime_error("Size of DB is not consistent");
	}
}
