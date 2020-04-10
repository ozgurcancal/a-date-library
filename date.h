#pragma once
#ifndef DATE_H
#define DATE_H
#include <iosfwd>
#include <ctime>


class Date {
private:

	int day = 0;
	int month = 0;
	int year = 0;
	time_t timer = time(NULL);

	static int md[12];

	static const std::string my[12];

	Date& gun_cikar(Date&, int)const;   //tarihten istenildiği kadar gün çıkaran üye fonksiyon
	int month_to_date()const;	//tarihin sadece aylarını güne dönüştürür
	int number_of_leapyear()const;   //o yıla kadar kaç artık yıl geçtiğini hesaplayan üye fonksiyon

public:

	struct tm* ptr = localtime(&timer);

	static constexpr int year_base = 1900;  //1		sınıfın hizmet verdiği en küçük yıl değeri
	static constexpr int random_min_year = 1940;  //2	random_date işlevinin üreteceği tarih için en küçük yıl değeri		  
	static constexpr int random_max_year = 2020;  //3	random_date işlevinin üreteceği tarih için en büyük yıl değeri
	enum class WeekDay { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }; //4	Haftanın günü için enum class türü

	Date& gun_topla(Date&, int)const;  //tarihe istenildiği kadar gün ekleyen üye	fonksiyon
	
	Date(); //5		Varsayılan kurucu işlev: Date nesnesini 01-01-1900 tarihi ile oluşturacak
	Date(int d, int m, int y);  //6		Date nesnesini gün, ay, yıl değeri ile oluşturacak kurucu işlev
	Date(const char* p);  //7		Date nesnesini formatlanmış yazıdan alacağı tarih değeri ile oluşturacak. Format: gg/aa/yil
	Date(std::time_t timer); //8	Date nesnesini "calender time" değerinden dönüştüreceği tarih değeri ile oluşturacak.

	int get_month_day()const; //9	Ayın gününü döndürüyor.
	int get_month()const; //10		Ay değerini döndürüyor. (Ocak 1, Şubat 2, ...)  
	int get_year()const; //11		Tarihin yıl değerini döndürüyor
	int get_year_day()const; //12	Yılın gününü döndürüyor (01 Ocak ---> 1 31 Aralık---> 365 ya da 366  

	WeekDay get_week_day(const Date& date)const; //13	Haftanın gününü döndürüyor.

	Date& set_month_day(int day); //14	Tarihin ayın günü değerini değiştiriyor.
	Date& set_month(int month); //15	Tarihin ayını değiştiriyor
	Date& set_year(int year); //16	Tarihin yılını değiştiriyor.
	Date& set(int day, int mon, int year); //17	Tarihi değiştiriyor.

	Date operator-(int day); //18	Tarihten gün çıkartan const üye operatör işlevi.Geri dönüş değeri elde edilen tarih olacak.

	Date& operator+=(int day); //19	Tarihi gelen gün kadar arttıran üye operatör işlevi.Geri dönüş değeri* this 

	Date& operator-=(int day); //20 Tarihi gelen gün kadar eksilten üye operatör işlevi.Geri dönüş değeri* this 
	Date& operator++(); //21		Önek ++ operatörünü yükleyen işlev. (İşlevin referans döndürüyor).
	Date operator++(int); //22		Sonek ++ operatörünü yükleyen işlev. (İşlevin referans döndürmüyor).

	Date& operator--(); //23	Önek -- operatörünü yükleyen işlev. (İşlevin referans döndürdüğüne dikkat ediniz).
	Date operator--(int); //24	Sonek -- operatörünü yükleyen işlev. (İşlevin referans döndürmediğine dikkat ediniz).

	static Date random_date(); //25	Artık yıl testi yapan sınıfın static üye işlevi.

	static bool isleap(int y); //26	Artık yıl testi yapan sınıfın static üye işlevi.

	friend std::ostream& operator << (std::ostream& out, const Date::WeekDay b);   //haftanın gününü yazdıran global operator işlevi

	friend bool operator<(const Date&, const Date&);
	friend bool operator==(const Date&, const Date&);
	friend int operator-(const Date& d1, const Date& d2); //iki tarihi çıkaran operator fonksiyon

	friend std::ofstream& operator << (std::ofstream& ofs, Date& d);
	
	friend std::ostream& operator<<(std::ostream& os, const Date& date); //31
	friend std::istream& operator>>(std::istream& is, Date& date); //32
};

bool operator<(const Date&, const Date&); //27	Date nesnelerinin karşılaştırılmasını sağlayacak global operatör işlevleri
bool operator<=(const Date&, const Date&); //27
bool operator>(const Date&, const Date&); //27
bool operator>=(const Date&, const Date&); //27
bool operator==(const Date&, const Date&); //27
bool operator!=(const Date&, const Date&); //27
//
int operator-(const Date& d1, const Date& d2); //28	İki tarih arasındaki gün farkını döndüren global operatör işlevi
Date operator+(const Date& date, int n); //29	Gelen tarihten n gün sonrasını döndüren global operatör işlevleri
Date operator+(int n, const Date&); //29

Date::WeekDay& operator++(Date::WeekDay& r); //30  //sadece wwekdayle işimiz var diğer öğelerle bir işimizi olmadığı için friendlik vermeye gerek yok
Date::WeekDay& operator++(Date::WeekDay& r, int); //30
Date::WeekDay& operator--(Date::WeekDay& r); //30	
Date::WeekDay& operator--(Date::WeekDay& r, int); //30
//

std::ostream& operator<<(std::ostream& os, const Date& date); //31		Date nesnelerinin değerlerini çıkış akımlarına yazdıracak global operatör işlevi (inserter) Formatlama şöyle olmalı: 31 Ekim 2019 Persembe
std::istream& operator>>(std::istream& is, Date& date); //32	Date nesnelerine giriş akımlarından aldığı karakterlerden oluşturulacak değeri yerleştiren global operatör işlevi(extractor) Formatlama: gg / aa / yyyy(ayıraç olarak istenilen bir karakter kullanılabilir.

#endif
