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
//	cout << "DEBUG print db_set before search" << endl << "DEBUG " << db_set_ << endl;
//	vector<Date> dates_found;
	map<Date, set<string>> del_map_set;		//Словарь дат в множество событий. Заношу сюда удаленные события.
	int count_del = 0;		//все равно надо выводить количество удаленных событий
	//прохожу итератором по базе с множествами сравнивая каждую пару год и событие функцией predicate. Если они подходят
	//под заданное условие - добавляю их во временную БД c множеством, чтобы их потом можно было вычесть
	for (auto it_m = db_set_.begin(); it_m != db_set_.end(); ++it_m) {
		auto &val_set = it_m->second;
		for (auto it_s = val_set.begin(); it_s != val_set.end(); ++it_s) {
			auto date = it_m->first;
			if (predicate(date, *it_s)) {
				++count_del;
//				dates_found.push_back(date);
				del_map_set[date].insert(*it_s);
			}
		}
	}
//	cout << "DEBUG print map of events to delete:\nDEBUG " << del_map_set << endl;			//REMOVE IT AFTER TEST!!!
	//если были удаления из базы, надо пройтись по базе и удалить ненужные события по отмеченным датам
	if (count_del > 0) {
//		cout << "DEBUG print db_set after search" << endl << "DEBUG " << db_set_ << endl;
//		unique(dates_found.begin(),dates_found.end());
/*		map<Date, vector<string>> temp_vec(db_vec_);		//копия словаря дат в вектор событий. для итерации по нему
		for (auto it_m = temp_vec.begin(); it_m != temp_vec.end(); ++it_m) {
			auto date = it_m->first;
			std::map<Date, std::set<string> >::iterator search = del_map_set.find(date);
			if (search != del_map_set.end()) {
				set<string> set_dif;
				auto &val_set = it_m->second;
				set_difference(val_set.begin(), val_set.end(), del_map_set[date].begin(), del_map_set[date].end(),
						std::inserter(set_dif, set_dif.end()));
				db_set_[date] = set_dif;
			}

		}*/
		if (del_map_set == db_set_) {
//			cout << "DEBUG есть полное совпадение по БД, грохаю все" << endl;
			db_set_.clear();
			db_vec_.clear();
			return count_del;
		} else {
			for (auto it_m = del_map_set.begin(); it_m != del_map_set.end(); ++it_m) {
				auto date = it_m->first;
				auto &val_set = it_m->second;
				if (val_set == db_set_[date]) {
//					cout << "DEBUG Есть совпадение по множеству на дату, удаляю" << endl;
//					cout << "DEBUG " << val_set << endl << "DEBUG " << del_map_set[date] << endl;
					db_set_.erase(date);
					db_vec_.erase(date);
					continue;
				}
				//!!!***Не совсем понятно, зачем я удаляю тут все элементы вектора. Похоже удаление идет без проверки необходимости этого действия. Надо поправить
				for (auto it_s = val_set.begin(); it_s != val_set.end(); ++it_s) {
//					удаляю элементы вектора сдвигая итератор начала, который получаю алгоритмом remove
					db_vec_[date].erase(remove(db_vec_[date].begin(), db_vec_[date].end(), *it_s), db_vec_[date].end());
				}
				set<string> set_dif;
				set_difference(val_set.begin(), val_set.end(), del_map_set[date].begin(), del_map_set[date].end(),
											std::inserter(set_dif, set_dif.end()));
				db_set_[date] = set_dif;
			}
		}

	}
	return count_del;
//	condition->Evaluate()
}

vector<string> Database::FindIf (function<bool(const Date& date, const string& event)> predicate) const {
	vector<string> founded_events;
	for (auto it_m = db_vec_.begin(); it_m != db_vec_.end(); ++it_m) {
		auto &val_vec = it_m->second;
		for (auto it_v = val_vec.begin(); it_v != val_vec.end(); ++it_v) {
			if (predicate(it_m->first, *it_v)) {
//				Date tdate = it_m->first;
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
		throw invalid_argument("Vector is empty");
	}
/*	try {
		if (db_vec_.at(date).empty()) {
			throw invalid_argument("");
		}
		stringstream ss;
		ss << date << " " << db_vec_.at(date).back();
		return ss.str();
	}
	catch (out_of_range&) {
	}*/
	auto it = db_vec_.upper_bound(date);
	/*if (it == db_vec_.end()) {
		throw invalid_argument("Upperbound equals end of vector");
	}
	else*/ if (it == db_vec_.begin()) {
//		throw invalid_argument("Upperbound equals begin of vector");
		return "No entries";
	} else {
		it--;
		if (!it->second.empty()) {
			stringstream ss;
			ss << it->first << " " << it->second.back();
			return ss.str();
		}
		else {
			throw invalid_argument("");
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
