// ConsoleApplication11_QuadrEq_6109_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Input equation coeffitients (use space to split):" << endl;
	double a = 0;
	double b = 0;
	double c = 0;
	cin >> a >> b >> c;

	

	if (a == 0) {
		cout << "Not a quadratic equation" << endl;
	} else {
		double d = 0;
		d = b*b - 4*a*c;
		double x1 = 0;
		double x2 = 0;

		cout << "D = " << d << endl;
		if (d < 0) {
			//no roots
			cout << "D < 0 - No roots" << endl;
		} else if (d == 0) {
				//one root
				x1 = (-1)*b / (2*a);
				cout << "One root, x = " << x1;
			} else {
				//two roots
				x1 = ((-1)*b + sqrt(d)) / (2*a);
				x2 = ((-1)*b - sqrt(d)) / (2*a);
				cout << "Two roots, x1 = " << x1 << "   x2 = " << x2;
			}
		
		cout << endl;
		

	}

	return 0;
}

