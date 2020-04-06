
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include<iomanip>
#include "Date.h"
#include <sstream>
#include<ctime>
#include <map>
#include <cstdlib>
#include <chrono>
#include <locale.h>

const int Date::md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const std::string Date::my[12] = { "ocak","subat","mart","nisan","mayis","haziran","temmuz","agustos","eylul","ekim","kasim","aralik" };

Date::Date() :day{ 1 }, month{ 2 }, year{ 1990 } {	}
	
Date::Date(int d, int m, int y) : day{ d }, month{ m }, year{ y } {	}

Date::Date(const char* input) {
	if (std::sscanf(input, "%d/%d/%d", &day, &month, &year));
	else
		std::cout << "pars ederken hata meydana geldi!!";

}

Date::Date(std::time_t timer) {

	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year = ptr->tm_year;
}

int Date::get_month_day() const {

	return (day);
}

int Date::get_month() const {

	return(month);
}

int Date::get_year() const {

	return(year);
}

int Date::get_year_day() const {

	int d = day;
	int m = month;

	while (--m) {

		d += md[month];

	}
	return d;
}


Date::WeekDay Date::get_week_day() const {

	int i = ptr->tm_wday;

	std::map<int, WeekDay> m;
	m[0] = WeekDay::Sunday;
	m[1] = WeekDay::Monday;
	m[2] = WeekDay::Tuesday;
	m[3] = WeekDay::Wednesday;
	m[4] = WeekDay::Thursday;
	m[5] = WeekDay::Friday;
	m[6] = WeekDay::Saturday;


	WeekDay a = m[i];

	return a;

}

Date& Date::set_month_day(int d) {

	day = d;
	return *this;
}

Date& Date::set_month(int m) {

	month = m;
	return *this;
}

Date& Date::set_year(int y) {

	year = y;
	return *this;
}

Date& Date::set(int d, int m, int y) {

	day = d;
	month = m;
	year = y;
	return *this;
}


void Date::print_date() {

	std::printf("%02d-%02d-%04d ", day, month, year);  
}


Date& Date::gun_cikar(Date& date, int x)const {


	int& gün = date.day; int& ay = date.month; int& yıl = date.year;

	gün = gün - x;

	while (gün < 1) {
		ay--;
		while (ay < 1) {
			yıl--;
			ay = 12 + ay;
		}
		gün = md[ay - 1] + gün;

	}

	return date;
}

Date& Date::gun_topla(Date& date, int x)const {     


	int& gün = date.day; int& ay = date.month; int& yıl = date.year;

	gün = gün + x;

	if (ay > 0) {

		while (gün > md[ay - 1]) {

			gün = gün - md[ay - 1];
			ay++;

			while (ay > 12)
			{
				ay = 12 - ay;
				yıl++;
			}
		}
	}
	return date;

}

int Date::month_to_date(int month)const {

	int day = 0;
	while (month) {
		day += md[month];
		month--;
	}

	return day;
}

int Date::number_of_leapyear()const {
	int count = 0;
	int y = year;
	while (y--) {
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400)) {

			count++;
		}
	}
	return count;
}

Date Date:: operator-(int x) {


	return (gun_cikar(*this, x));
}

Date& Date:: operator += (int x) {


	return gun_topla(*this, x);
}

Date& Date:: operator-=(int x) {


	return gun_cikar(*this, x);
}

Date& Date:: operator++() {  //ön ek


	return gun_topla(*this, 1);
}

Date Date::operator++(int) {  //son ek    

	Date temp{ *this };

	gun_topla(*this, 1);

	return temp;
}

Date& Date:: operator--() {


	return gun_cikar(*this, 1);
}

Date Date:: operator--(int) {

	Date temp{ *this };

	gun_cikar(*this, 1);


	return temp;
}

Date Date::random_date() {


	Date rast;

	rast.year = (rand() % 80) + rast.random_min_year;
	rast.month = (rand() % 12) + 1;
	int day = rast.md[rast.month - 1];  //random belirlenen aydaki gün sayısı
	rast.day = (rand() % day) + 1;

	return rast;
}

constexpr bool Date::isleap(int year) {

	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400)) {
		std::cout << "girdiginiz yil bir artik yildir";
		return 1;
	}
	else {
		std::cout << "girdiginiz yil artik yil degil";
		return 0;
	}
}


bool operator<(const Date& self, const Date& obj) {

	if (self.year < obj.year)
		return 1;
	else if (self.year == obj.year && self.month < obj.month)
		return 1;
	else if (self.year == obj.year && self.month == obj.month && self.day < obj.day)
		return 1;
	else
		return 0;
}

bool operator<=(const Date& self, const Date& obj) {

	return !(obj < self);
}

bool operator>(const Date& self, const Date& obj) {

	return obj < self;
}

bool operator>=(const Date& self, const Date& obj) {

	return !(self < obj);
}

bool operator==(const Date& self, const Date& obj) {

	if (self.year == obj.year && self.month == obj.month && self.day == obj.day)
		return 1;
	else
		return 0;
}

bool operator!=(const Date& self, const Date& obj) {

	return !(self == obj);
}

int operator-(const Date& self, const Date& obj) {  //iki tarihi çıkaran fonksiyon

	if (self > obj) {  //eğer bizim tarihimiz çıkarılan tarihten büyükse güne çevirilmiş tarihleri birbirinden çıkar.

		int day = (self.year - obj.year) * 365 + self.number_of_leapyear() - obj.number_of_leapyear() + (self.month_to_date(self.month) - obj.month_to_date(obj.month)) + (self.day - obj.day);

		std::cout << "iki tarih arasinda " << day << " gun fark var";

		return day;
	}

	else {
		std::cout << "ikinci deger daha buyuk hata degeri: ";
		return -1;  //hata degeri olarak -1 donduruldu
	}

}

Date operator+(Date& date, int n) {   // tarihten n gün sonrasını veren fonksiyon


	return date.gun_topla(date, n);
}


Date operator+(int n, Date& date) {

	return date.gun_topla(date, n);
}


Date::WeekDay& weekday_arttır(Date::WeekDay& r) {

	int a = (static_cast<int>(r) + 1);
	if (a > 6)
		a = a % 7;
	r = static_cast<Date::WeekDay>(a);
	return r;

}
Date::WeekDay& weekday_azalt(Date::WeekDay& r) {

	int a = (static_cast<int>(r) - 1);
	if (a < 0)
		a += 7;
	r = static_cast<Date::WeekDay>(a);
	return r;

}

Date::WeekDay& operator++(Date::WeekDay& r) {  

	return weekday_arttır(r);
}

Date::WeekDay& operator++(Date::WeekDay& r, int) {

	Date::WeekDay static temp{ r };

	weekday_arttır(r);

	return temp;

}
Date::WeekDay& operator--(Date::WeekDay& r) {


	return weekday_azalt(r);

}
Date::WeekDay& operator--(Date::WeekDay& r, int) {

	Date::WeekDay static temp{ r };

	weekday_azalt(r);

	return temp;

}

std::ostream& operator<<(std::ostream& os, const Date::WeekDay& f) { 


	int Val = static_cast<int>(f);

	switch (Val) {
	case 0:return os << "Pazar";
	case 1:return os << "Pazartesi";
	case 2:return os << "Salı";
	case 3:return os << "Çarşamba";
	case 4:return os << "Perşembe";
	case 5:return os << "Cuma";
	case 6:return os << "Cumartesi";
	default: return os << Val;
	}
}

std::ostream& operator << (std::ostream& os, const Date& d) {

	os << d.day << " " << d.my[d.month - 1] << " " << d.year << " " << d.get_week_day();

	return os;
}

std::istream& operator >> (std::istream& is, Date& d) {

	char c = '/';
	is >> d.day >> c >> d.month >> c >> d.year;

	return is;
}
