
#include <vector>
#include <iostream>

#include <iomanip>

using namespace std;


int main()
{

	vector<long long> c;
	c.push_back(1); 		// c[0] = 1
	
	vector<double> b;
	b.push_back(1);			// b[0] = 1
	
	vector<double> a;
	a.push_back(1);			// a[0] = 1
	
	vector<double> sum;
	sum.push_back(1);		// sum[0] = 1

	vector<double> eps;		// no push_back(), начальный элемент будет определяться в самом цикле, поэтому по eps будем отслеживать существование нужной строки
	
	double x;
	double alpha;

	cin >> x >> alpha;

	double limit = exp(x)*cos(x);

	long long zerobuf = 0;						// ???

	if ((alpha - (int)alpha) == 0) { // Z

		if (alpha > eps.size())

			for (int i = eps.size(); i <= alpha - 1; ++i) {

				switch (i % 4)						// creating c[i+1]
				{
				case 0: {
					c.push_back(c[i]);
					break;
				}
				case 1: {
					zerobuf = c[i] * (-2);
					c.push_back(0);
					break;
				}
				case 2: {
					c.push_back(zerobuf);
					break;
				}
				case 3: {
					c.push_back(c[i] * 2);
					break;
				}
				}

				b.push_back(b[i] * x / (i + 1));			// b[i+1] = b[i] * x/(i + 1) 

				a.push_back(b[i + 1] * c[i + 1]);				// a[i+1] = b[i+1]*c[i+1]

				sum.push_back(sum[i] + a[i + 1]);			// sum[i+1] = sum[i] + a[i+1]

															//eps.push_back( abs(a[i+1]/sum[i]) );		// eps[i] = abs(a[i+1]/sum[i])
				eps.push_back(abs(limit - sum[i]));		// eps[i] = abs(limit - sum[i])

				cout << setprecision(15) << i << '\t' << a[i] << '\t' << sum[i] << '\t' << eps[i] << endl;

			}
		else
		{
			cout << setprecision(15) << alpha << '\t' << a[alpha - 1] << '\t' << sum[alpha - 1] << '\t' << eps[alpha - 1] << endl;
		}

		
	}

	system("pause");
	return 0;
}