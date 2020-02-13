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

ostream Database::Print (ostream& ) const {

}
