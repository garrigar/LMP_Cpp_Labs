// Practice6_6110.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "std_lib_facilities.h"

class my_date {
public:
	enum Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
	my_date(int dd, Month mm, int yy) : d(dd), m(mm), y(yy) { check(); }
	my_date() : d(1), m(jan), y(1) {};
	int day() const { return d; }
	Month month() const { return m; }
	int year() const { return y; }
	bool is_leap_year() const
	{
		return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
	}
	int days_in_month() const
	{
		return is_leap_year() ? day_count_leap[m - 1] : day_count[m - 1];
	}
	my_date& operator++() //pre
	{
		if (d < days_in_month())
			++d;
		else {
			d = 1;
			m = (m == dec) ? jan : Month(m + 1);
			if (m == jan) {
				++y;
				check_year();
			}
		}
		return *this;
	}
	my_date operator++(int) //post
	{
		my_date tmp(*this);
		operator++();
		return tmp;
	}


	my_date& operator--() //pre
	{
		if (d > 1)
			--d;
		else {
			m = (m == jan) ? dec : Month(m - 1);
			if (m == dec) {
				--y;
				check_year();
			}
			d = days_in_month();
		}
		return *this;
	}

	my_date operator--(int) //post
	{
		my_date tmp(*this);
		operator--();
		return tmp;
	}
	my_date& operator=(const my_date& a)
	{
		d = a.d;
		m = a.m;
		y = a.y;
		return *this;
	}
private:
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
		if ((d<1) || (d > days_in_month()))
			error("Wrong day!!!");
	}
	void check_month()
	{
		if ((m < 1) || (m > 12))
			error("Wrong month!!!");
	}
	void check_year()
	{
		if (y < 1)
			error("Wrong year!!!");
	}
	int d;
	Month m;
	int y;
};

ostream& operator<<(ostream& os, const my_date& date)
{
	char old_fill = os.fill('0');
	return os << setw(2) << date.day() << '.' << setw(2) << date.month() << '.' << setw(4) << date.year() << setfill(old_fill);
}

istream& operator>>(istream& is, my_date& date)
{
	int y, m, d;
	char p1, p2;
	is >> d >> p1 >> m >> p2 >> y;
	if (!is)
		return is;
	if (p1 != '.' || p2 != '.') {
		is.clear(ios::failbit);
		return is;
	}
	try {
		date = my_date(d, my_date::Month(m), y);
	}
	catch (runtime_error&) {
	}
	return is;
}
int main()
{
	try {
		my_date date(1, my_date::jan, 17);
		//cout << date.day() << '.' << date.month() << '.' << date.year() << endl;
		cout << date << endl;
		cout << date.is_leap_year() << endl;
		cout << date.days_in_month() << endl;
		my_date date2 = date--;
		//cout << "Date: "<<date.day() << '.' << date.month() << '.' << date.year() << endl;
		cout << "Date: " << date << endl;
		//cout << "Date2: " << date2.day() << '.' << date2.month() << '.' << date2.year() << endl;
		cout << "Date2: " << date2 << endl;
		cout << "Enter date3: " << endl;
		my_date date3;
		cin >> date3;
		ofstream ofs("file_date.txt");
		if (!ofs) 
			error("cant open output file");
		ofs << date3 << endl;
		ifstream ifs("file_date.txt");
		if (!ifs)
			error("cant open input file");
		my_date date4;
		ifs >> date4;
		cout << date4 << endl;

	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
	//system("pause");
	keep_window_open();
	return 0;
}
