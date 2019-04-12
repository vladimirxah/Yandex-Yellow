/*
 * phone_number.cpp
 *
 *  Created on: 12 апр. 2019 г.
 *      Author: goncharov
 */
#include <sstream>
#include <exception>
#include <iostream>
#include "phone_number.h"

PhoneNumber::PhoneNumber(const string &international_number) {
	/*Принимает строку в формате +XXX-YYY-ZZZZZZ
	Часть от '+' до первого '-' - это код страны.
	Часть между первым и вторым символами '-' - код города
	Всё, что идёт после второго символа '-' - местный номер.
	Код страны, код города и местный номер не должны быть пустыми.
	Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.*/
	stringstream ss(international_number);
	if (ss.get() != '+') {
		throw invalid_argument("First symb is not +");
	}
	if (ss.peek() == '-') {
		throw invalid_argument("+-... format");
	}
	getline(ss, country_code_, '-');
//	country_code_ = ss.getline(6, '-');
//	cout << country_code_ << endl;
	ss.unget();
//	cout << (char)ss.peek() << endl;
	if (ss.get() != '-') {
		throw invalid_argument("Do not have - after country code");
	}
	getline(ss, city_code_, '-');
	ss.unget();
	if (ss.get() != '-') {
		throw invalid_argument("Do not have - after city code");
	}
	getline(ss, local_number_);
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}


//Example
/*
#include <stdexcept>
#include <string>
#include <sstream>
#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream is(international_number);

  char sign = is.get();
  getline(is, country_code_, '-');
  getline(is, city_code_, '-');
  getline(is, local_number_);

  if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
  }
}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

string PhoneNumber::GetCityCode() const {
  return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
  return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
*/

