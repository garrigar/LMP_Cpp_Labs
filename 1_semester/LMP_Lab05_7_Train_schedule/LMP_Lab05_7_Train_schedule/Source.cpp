#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct IncorrectDataExeption { };

class TrainRunInfo {
private:
	string from, to;
	struct Time
	{
		int h;
		int m;
	};
	Time start_time, stop_time, run_time;

	void recalc_run_time() {
		run_time.m = stop_time.m - start_time.m;
		run_time.h = stop_time.h - start_time.h;
		if (run_time.m < 0) {
			run_time.m += 60;
			--run_time.h;
		}
		if (run_time.h < 0)
			run_time.h += 24;
	}

public:
	// constructors

	TrainRunInfo() {} // empty constructor
	TrainRunInfo(string start_loc, Time start_t, string stop_loc, Time stop_t) { // full data constructor
		from = start_loc;
		to = stop_loc;
		start_time = start_t;
		stop_time = stop_t;
	}
	
	Time get_run_time() {
		return run_time;
	}

	friend ostream& operator<<(ostream &, const TrainRunInfo &);
	friend istream& operator>>(istream &, TrainRunInfo &);

};

ostream& operator<<(ostream &os, const TrainRunInfo &tri) {
	return os << setfill('0') 
			<< tri.from << ' '
			<< setw(2) << tri.start_time.h << ':' << setw(2) << tri.start_time.m << ' '
			<< tri.to << ' ' 
			<< setw(2) << tri.stop_time.h << ':' << setw(2) << tri.stop_time.m << ' '
			<< setw(2) << tri.run_time.h << ':' << setw(2) << tri.run_time.m;
}

istream& operator>>(istream &is, TrainRunInfo &tri) {
	
	is >> tri.from >> tri.start_time.h;
	is.ignore(); // skipping ":"
	is >> tri.start_time.m >> tri.to >> tri.stop_time.h;
	is.ignore(); // skipping ":"
	is >> tri.stop_time.m;

	tri.recalc_run_time();
	
	return is;
}

int main(){

	setlocale(LC_ALL, "");

	vector<TrainRunInfo> entry;
	char choise;
	int n;

	cout << "Read from file or concole? (f/c) >";

	cin >> choise;
	if (choise == 'f') {

		ifstream fin("input.txt");
		if (!fin.is_open()) {
			cout << "File not open!" << endl;
			system("pause");
			return 1;
		}
		/*
		while (!fin.eof()) {
			TrainRunInfo tri;
			fin >> tri;
			entry.push_back(tri);
		}
		*/
		
		try	{
			
			fin >> n;
			if (fin.fail())
				throw IncorrectDataExeption();
		
			for (int i = 0; i < n; i++) {
				TrainRunInfo tri;
				fin >> tri;
				if (fin.fail())
					throw IncorrectDataExeption();
				entry.push_back(tri);
			}
		}
		catch (...) {
			cout << "Incorrect input data!" << endl;
			fin.close();
			system("pause");
			return 1;
		}

		fin.close();

	}
	else if (choise == 'c')
	{
		cout << "Enter the number of items > ";
		cin >> n;
		cout << "Enter items:" << endl;
		for (int i = 0; i < n; i++) {
			TrainRunInfo tri;
			cin >> tri;
			entry.push_back(tri);
		}
	}
	else
	{
		cout << "Incorrect control" << endl;
		system("pause");
		return 1;
	}

	cout << "Write into file or into concole? (f/c) >";
	cin >> choise;
	if (choise == 'f') {
		ofstream fout("output.txt");
		for (size_t i = 0; i < entry.size(); i++)
			fout << entry[i] << endl;
		fout.close();
	}
	else if (choise == 'c')
		for (size_t i = 0; i < entry.size(); i++)
			cout << entry[i] << endl;
	else
	{
		cout << "Incorrect control" << endl;
		system("pause");
		return 1;
	}

	system("pause");
	return 0;
}