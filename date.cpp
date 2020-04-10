
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include<iomanip>
#include "date.h"
#include <sstream>
#include<ctime>
#include <map>
#include <cstdlib>
#include <chrono>
#include <locale.h>
#include <vector>
#include <random>
#include<fstream>

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

int Date::md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const std::string Date::my[12] = { "ocak","subat","mart","nisan","mayis","haziran","temmuz","agustos","eylul","ekim","kasim","aralik" };

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

Date::WeekDay Date::get_week_day(const Date& date) const { 

	Date d{ 23,2,2020 };
	int wd = 0;   //23 şubat 2020 tarihi pazar gününe denk gelmektedir ve istenilen günün değeri bu gün ismine göre hesaplanır.

	int i = ((date - d) + wd) % 7;
	if (i < 0)
		i += 7;

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

Date& Date::gun_cikar(Date& date, int x)const {

	if (isleap(year))  
		md[1] = 29;

	int& gun = date.day; int& ay = date.month; int& yil = date.year;

	gun = gun - x;   //günden istenilen değer çıkarılır, eğer negatifse aydan gün alınır ay negatif olursa yıldan ay alınır.

	while (gun < 1) {   
		ay--;
		while (ay < 1) {
			yil--;
			ay = 12 + ay;
		}
		gun = md[ay - 1] + gun;

	}

	return date;
}

Date& Date::gun_topla(Date& date, int x)const {     


	int& gun = date.day; int& ay = date.month; int& yil = date.year;


	gun = gun + x;
	if (isleap(year))
		md[1] = 29;


	while (gun > (md[ay - 1])) {   //?????  	Warning	C6385	Reading invalid data from 'md':  the readable size is '48' bytes, but '-8' bytes may be read.	


		gun = gun - (md[ay - 1]);
		ay++;

		while (ay > 12)
		{
			ay = 12 - ay;
			yil++;
		}

	}

	return date;

}

int Date::month_to_date()const {

	if (isleap(year))
		md[1] = 29;

	unsigned m = (month);
	int day = 0;

	while (--m) {
		day += md[m - 1];
	}

	return day;
}

int Date::number_of_leapyear()const {

	int count = 0;
	int y = year;

	while (--y) {
		if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) {

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

Date& Date:: operator++() { 


	return gun_topla(*this, 1);
}

Date Date::operator++(int) {   

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

bool  Date::isleap(int year) {

	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400)) {

		return 1;
	}

	return 0;

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


int operator-(const Date& self, const Date& obj) { 

	int day_self = self.year * 365 + self.number_of_leapyear() + self.month_to_date() + self.day;
	int day_obj = obj.year * 365 + obj.number_of_leapyear() + obj.month_to_date() + obj.day;

	return day_self - day_obj;

}

Date operator+(Date& date, int n) {  

	return date.gun_topla(date, n);
}


Date operator+(int n, Date& date) {

	return date.gun_topla(date, n);
}


Date::WeekDay& weekday_arttir(Date::WeekDay& r) {

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

	return weekday_arttir(r);

}

Date::WeekDay& operator++(Date::WeekDay& r, int) {

	Date::WeekDay static temp{ r };

	++r;

	return temp;

}
Date::WeekDay& operator--(Date::WeekDay& r) {

	return weekday_azalt(r);

}

Date::WeekDay& operator--(Date::WeekDay& r, int) {

	Date::WeekDay static temp{ r };

	--r;

	return temp;

}

std::ostream& operator<<(std::ostream& os, const Date::WeekDay& f) { 

	static const char* const p[] = { "Pazar", "Pazartesi", "Sali","Carsamba", "Persembe", "Cuma", "Cumartesi" };
	return os << p[static_cast<int>(f)];
}

std::ostream& operator << (std::ostream& os, const Date& d) {

	os << d.day << " " << d.my[d.month - 1] << " " << d.year << " " << d.get_week_day(d);

	return os;
}
std::ofstream& operator << (std::ofstream& ofs, Date& d) {

	ofs << d.day << " " << d.my[d.month - 1] << " " << d.year << " " << d.get_week_day(d);

	return ofs;
}

std::istream& operator >> (std::istream& is, Date& d) {

	char c = '/';
	is >> d.day >> c >> d.month >> c >> d.year;

	return is;
}


int main()
{
	//******test kodu 1**********//
	Date today{ 23, 2, 2020 };
	Date future_date{ 15, 1, 2021 };

	while (today < future_date) {
		std::cout << today++ << "\n";
	}
	
	//******test kodu 2**********//
	using namespace std;

	vector<Date> myvec;
	for (int i = 0; i < 20'000; ++i) {
		myvec.push_back(Date::random());
	}
	sort(myvec.begin(), myvec.end());
	ofstream ofs{ "tarihler.txt" };
	for (const auto &date : myvec)
		ofs << date << "\n";
	
}


