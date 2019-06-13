// Practice6_6109.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "std_lib_facilities.h"

class MyDate {
public:
	enum Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
	MyDate(int dd, Month mm, int yy) : d(dd), m(mm), y(yy) { check(); }
	int day() const { return d; }
	Month month() const { return m; }
	int year() const { return y; }
	bool is_leap_year() const
	{
		return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
	}
	int days_in_month() const { return is_leap_year() ? day_count_leap[m - 1] : day_count[m - 1]; }

	MyDate& operator++() 
	{
		if (d < days_in_month()) 
			++d;
		else {
			d = 1;
			if (m == dec) {
				m = jan;
				++y;
				check_year();
			}
			else
				m = Month(m+1);
		}
		return *this;
	}
	MyDate operator++(int)
	{
		MyDate tmp(*this);
		operator++();
		return tmp;
	}
	MyDate& operator--()
	{
		if (d > 1)
			--d;
		else {			
			if (m == jan) {
				m = dec;
				--y;
				check_year();
			}
			else
				m = Month(m - 1);
			d = days_in_month();
		}
		return *this;
	}
	MyDate operator--(int)
	{
		MyDate tmp(*this);
		operator--();
		return tmp;
	}

private:
	int d;
	int y;
	Month m;
	const vector<int> day_count = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	const vector<int> day_count_leap = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	void check()
	{
		check_year();
		check_month();
		check_day();
	}
	void check_day()
	{
		if (!((d >= 1) && (d <= days_in_month())))
			error("Wrong day!");
	}
	void check_month() 
	{
		if (!((m >= 1) && (m <= 12))) 
			error("Wrong month!");
		
	}
	void check_year()
	{
		if (y <= 0)
			error("Wrong year!");
	}


};

ostream& operator<< (ostream& os, const MyDate& date) 
{
	return os << date.day() << '.' << date.month() << '.' << date.year();
}

int main()
{
	//cout << "Hello, World!\n";
	try {
		MyDate date(1, MyDate::jan, 2011);
		//cout << date.day() << '.' << date.month() << '.' << date.year() << endl;
		cout << date << endl;
		
		cout << date.is_leap_year() << '\n';
		cout << date.days_in_month() << '\n';
		MyDate date2 = date--;
		//date.day() << '.' << date.month() << '.' << date.year() 
		cout << "date - " << date << endl;
		//<< date2.day() << '.' << date2.month() << '.' << date2.year() 
		cout << "date2 - " << date2 << endl;

	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
	keep_window_open();

	return 0;


}

