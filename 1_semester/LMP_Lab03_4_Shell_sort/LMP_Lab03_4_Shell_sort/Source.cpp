
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <ctime>

using namespace std;

const int MAX_OUT = 50;
enum vector_type {	MANUAL, RANDOM, ALMOST_SORTED };
const int GAP = 2; // for almost sorted -- max gap between swapped elements (recommended 1 or 2)

void vector_init(vector<int>& v, int len, int type) 
{
	switch (type) {
	case MANUAL: {
		int input;
		for (int i = 0; i < len; i++)
		{
			cin >> input;
			v.push_back(input);
		}
		break;
	}
	case RANDOM: {
		for (int i = 0; i < len; i++)
		{
			v.push_back(rand());
		}
		break;
	}
	case ALMOST_SORTED: {
		v.push_back(rand());
		for (int i = 1; i < len; i++)
		{
			v.push_back(v[i - 1] + rand());
		}
		int i = 0;
		int g;
		while (i + GAP < len)
		{
			g = 1 + rand() % GAP;
			swap(v[i], v[i + g]);
			i += (g + 1);
		}
		break;
	}
	}
}

void vector_print(const vector<int>& v) 
{
	int n = v.size();
	if (n > MAX_OUT)
		n = MAX_OUT;
	for (int i = 0; i < n; i++)
	{
		cout << v[i] << ' ';
	}
	cout << ((v.size() > MAX_OUT) ? "..." : "");
	cout << endl;
}

void shell_sort(vector<int>& a) 
{

	int len = a.size();
	int i, j, k;
	int x;

	int m = 0;
	/*	int d[] = { 1, 4, 10, 23, 57, 145, 356, 911, 1968, 4711, 11969, 27901,
		84801, 213331, 543749, 1355339, 3501671, 8810089, 21521774,
		58548857, 157840433, 410151271, 1131376761, 2147483647 };			*/
	int d[] = { 1, 4, 10, 23, 57, 132, 301, 701, 1750,		// A102549 from OEIS -- Optimal (best known) sequence of increments for shell sort algorithm. (n < 4000)
				4711, 11969, 27901,
				84801, 213331, 543749, 1355339, 3501671, 8810089, 21521774,
				58548857, 157840433, 410151271, 1131376761, 2147483647 };
	while (d[m] < len) ++m;

	while (--m >= 0) 
	{
		k = d[m];
		for (i = k; i < len; i++)	// k-sort
		{
			x = a[i];
			for (j = i; (j >= k) && (a[j - k] > x); j -= k) 
			{
				a[j] = a[j - k];
			}
			a[j] = x;
		}
	}
}

int main() 
{
	
	cout << "SHELL SORT" << endl;
	srand(time(0));

	vector<int> a;
	int n;
	int type;

	// -- for time count --
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);
	double time_std, time_shell; // in seconds
	// ------

	cout << "Input number of elements: > ";
	cin >> n;
	cout << "Input vector type: " << MANUAL << " - read from keyboard, " << RANDOM << " - create random, " << ALMOST_SORTED << " - create almost sorted > ";
	cin >> type;

	// INIT & PRINT
	cout << "Vector:" << endl;
	vector_init(a, n, type);
	if ((type == RANDOM) || (type == ALMOST_SORTED))
		vector_print(a);
	// INIT & PRINT END

	// STANDARD SORTING
	cout << "Standard sorting (std::sort):" << endl;
	vector<int> b(a); // b - vector for standard sorting
	
	QueryPerformanceCounter(&start);
	sort(b.begin(), b.end());
	QueryPerformanceCounter(&finish);
	time_std = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;

	vector_print(b);
	cout << "Time: " << time_std << " sec" << endl;
	// STANDRD END

	// SHELL SORTING
	cout << "Shell sort:" << endl;
	
	QueryPerformanceCounter(&start);
	shell_sort(a);
	QueryPerformanceCounter(&finish);
	time_shell = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;

	vector_print(a);
	cout << "Time: " << time_shell << " sec" << endl;
	// SHELL END

	cout << "Shell sort is faster on " << time_std - time_shell << " sec" << endl;

	system("pause");
	return 0;
}
