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

bool Date::check_date_validity(int day, unsigned month, int year) {
	bool x = ((month == 2 && isleap(year) && day > 29) || (day<0 || day>md[month-1]));   //şubatın 29 çektiği yıl hariç hiç bir ay md[] arrayinde belirtilen gün sayısını aşamaz.
	if ((year < 1900 || month < 0 || month >12 || x))
		throw BadDate("gecersiz tarih girdiniz\n");
	else
		return 1;
}

Date::Date() :day{ 1 }, month{ 2 }, year{ 1990 } {} 

Date::Date(int d, int m, int y) : day{ d }, month{ m }, year{ y } {

	check_date_validity(day, month, year);
}

Date::Date(const char* input) 
{

	if (std::sscanf(input, "%d/%d/%d", &day, &month, &year))
		check_date_validity(day, month, year);
	else 
		std::cout << "line42:pars ederken hata meydana geldi!!";
	
}

Date::Date(std::time_t timer)  {   //initialization list şeklinde olmuyor.?? sadece sabir değer veya argumanla ver ilk değer vereceksen

	day = ptr->tm_mday;
	month = ptr->tm_mon + 1;
	year= ptr->tm_year;
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

Date::WeekDay Date::get_week_day(const Date& date) const {  

	Date d{ 23,2,2020 };
	int wd = 0;   //23 şubat 2020 tarihi pazar gününe denk gelmektedir ve bir referans değeridir

	int i = ((date - d) + wd) % 7;
	if (i < 0)
		i += 7;
	 
	std::map<int, WeekDay> weekdays{ {0,WeekDay::Sunday},{1,WeekDay::Monday},{2,WeekDay::Tuesday},{3,WeekDay::Wednesday},{4,WeekDay::Thursday},{5,WeekDay::Friday},{6,WeekDay::Saturday} };

	return weekdays[i];

}

Date& Date::set_month_day(int d) {

	day = d;
	
	if((month == 2 && isleap(year) && d>29)|| (day<0 || day>md[month-1]))   //şubatın 29 çektiği yıl hariç hiç bir ay md[] arrayinde belirtilen gün sayısını aşamaz.
		throw std::logic_error("mantiksiz bir gun set edildi.");
	
	return *this;
}

Date& Date::set_month(int m) {

	month = m;
	if (month<0 || month>12)
		throw std::logic_error("mantiksiz bir ay set edildi.");
	return *this;
}

Date& Date::set_year(int y) {

	year = y;
	if (month < 1990 )
		throw std::logic_error("mantiksiz bir yil set edildi.");
	
	return *this;
}

Date& Date::set(int d, int m, int y) {

	day = d;
	month = m;
	year = y;
	check_date_validity(day, month, year);
	
	return *this;
}

int Date::md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 

const std::string Date::my[12] = { "ocak","subat","mart","nisan","mayis","haziran","temmuz","agustos","eylul","ekim","kasim","aralik" };

Date Date::gun_cikar(Date& date, int x)const {

	int& gun = date.day; int& ay = date.month; int& yil = date.year;

	gun = gun - x;
	if (isleap(year))
		md[1] = 29;
	while (gun < 1) {
		gun = md[ay - 1] + gun;
		ay--;
		while (ay < 1) {
			yil--;
			ay = 12 + ay;
		}
		

	}

	return date;
}

Date Date::gun_topla(Date& date, int x)const {   
	
	int& gun = date.day; unsigned ay = static_cast<unsigned>(date.month);  int& yil = date.year;

	gun = gun + x;
	if (isleap(year))
		md[1] = 29;


	while (gun > (md[ay - 1])) {    //gün bulunduğu ayın gününden fazla ise	ayı bir arttır daha sonra ay 12 den fazla olursa yılı bir arttır.

		gun = gun - (md[ay - 1]);
		ay++;

		while (ay > 12)
		{
			ay =  ay-12;
			yil++;
		}

	}

	date.month = ay;

	return date;

}

int Date::month_to_date()const {
	
	if (md[1]=isleap(year) ?  29 :  28);
	
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

Date Date:: operator-(int x) 
{
	return (gun_cikar(*this, x));
}

Date& Date:: operator += (int x) {

	gun_topla(*this, x);
	
	return *this;
}

Date& Date:: operator-=(int x) {

	gun_cikar(*this, x);
	
	return *this;
}

Date& Date:: operator++() {  //ön ek
	
	gun_topla(*this, 1);
	
	return *this;
}

Date Date::operator++(int) {  //son ek    

	Date temp{ *this };

	gun_topla(*this, 1);

	return temp;
}

Date& Date:: operator--() {
	
	gun_cikar(*this, 1);
	
	return *this;
}

Date Date:: operator--(int) {

	Date temp{ *this };

	gun_cikar(*this, 1);

	return temp;
}

Date Date::random_date() {

	Date random;

	random.year = (rand() % 80) + random.random_min_year;
	random.month = (rand() % 12) + 1;
	int day = random.md[random.month - 1];  //random belirlenen aydaki gün sayısı
	random.day = (rand() % day) + 1;

	return random;
}

bool  Date::isleap(int year) {

	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400==0)) {
	
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

	if (Date::isleap(self.year) && !Date::isleap(obj.year) && self.month_to_date() + self.day < 60)  //eksilen tarihin yılı artık yıl ise ve 29 şubattan erkense ve çıkan tarih artık yıl değilse ekstra günü ekleme.
		d--;


	return d;
}

Date operator+(Date& date, int n) {  

	return date.gun_topla(date, n);
}

Date operator+(int n, Date& date) {

	return date.gun_topla(date, n);
}

Date::WeekDay& operator++(Date::WeekDay& wd) {

	return wd = (wd == Date::WeekDay::Saturday ? Date::WeekDay::Sunday : static_cast<Date::WeekDay>(static_cast<int>(wd) + 1));
}

Date::WeekDay operator++(Date::WeekDay& wd, int) {

	Date::WeekDay temp{ wd };

	++wd;

	return temp;

}

Date::WeekDay& operator--(Date::WeekDay& wd) {

	return wd = (wd == Date::WeekDay::Sunday ? Date::WeekDay::Saturday : static_cast<Date::WeekDay>(static_cast<int>(wd) - 1));
}

Date::WeekDay operator--(Date::WeekDay& wd, int) {

	Date::WeekDay static temp{ wd };

	--wd;

	return temp;
}

std::ostream& operator<<(std::ostream& os, const Date::WeekDay f) { 

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

BadDate ::BadDate(const char* b) :str{ b } {} 
	

const char* BadDate::what() const noexcept {
					
	return str;
}



int main() try
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
	
	//******test kodu 3**********//
	Date::WeekDay wd{ Date::WeekDay::Sunday };

	for (int i = 0; i < 10; ++i) {
		std::cout << wd++ << " ";
	}
	
}

catch (BadDate& e) {
	std::cerr<<e.what();
}

catch (std::logic_error& e) {
	std::cout <<"Logic_error: "<< e.what();
}
