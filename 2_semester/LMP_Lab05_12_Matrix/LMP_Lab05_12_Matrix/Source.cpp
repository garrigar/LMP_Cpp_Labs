#include "matrix.hpp"
#include "square_matrix.hpp"

#include <iostream>

using namespace std;

int main() {
	cout << "...MATRIXES..." << endl;

	Matrix e;
	cout << "Identity matrix:" << endl << e << endl;

	cout << "Matrix A: " << endl;
	Matrix a(3, 4);
	a(0, 0) = 1;
	a(1, 1) = 2;
	a(2, 2) = 7;
	cout << a << endl;
	cout << "Transponded: " << endl << a.getTranspondedMatrix() << endl;

	cout << "Let's have some fun" << endl;

	try {
		cout << "Input matrix A dimensions n and m: ";
		int n, m;
		cin >> n >> m;
		Matrix a(n, m);
		cout << "Input matrix A: " << endl;
		cin >> a;

		cout << "Input matrix B dimensions n and m: ";
		cin >> n >> m;
		Matrix b(n, m);
		cout << "Input matrix B: " << endl;
		cin >> b;

		cout << "What you want to do?" << endl;
		cout << "1 +\n2 -\n3 *\n4 * by number\n5 / by number\n";
		int ch;
		cin >> ch;

		Matrix c;
		double d;
		switch (ch)
		{
		case 1:

			c = a + b;
			break;
		case 2:

			c = a - b;
			break;
		case 3:

			c = a * b;
			break;
		case 4:
			cout << "Input d: ";
			cin >> d;
			c = a * d;
			break;
		case 5:
			cout << "Input d: ";
			cin >> d;
			c = a / d;
			break;
		default:
			break;
		}

		cout << "Result:" << endl << c << endl;

		cout << "Let's have some fun with square matrixes" << endl;
		cout << "Input matrix A dimension N: ";
		cin >> n;
		SquareMatrix g(n);
		cout << "Input matrix A: " << endl;
		cin >> g;

		cout << "det A = " << g.determinant() << endl;
		cout << "trace A = " << g.trace() << endl;

	}
	catch (Matrix::Error& e) {
		cout << "Error! " << e.what() << endl;
	}
	system("pause");
}
