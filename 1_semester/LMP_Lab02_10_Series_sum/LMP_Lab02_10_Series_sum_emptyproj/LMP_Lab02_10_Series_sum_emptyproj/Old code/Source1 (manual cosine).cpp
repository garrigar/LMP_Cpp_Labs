
#define _USE_MATH_DEFINES  

#include <cmath>
#include <vector>
#include <iostream>

#include <iomanip>

using namespace std;


int main()
{
	const double COS_PI_4 = 1/sqrt(2);
	
	double cosine_pi_4[] = {1, COS_PI_4, 0, -COS_PI_4, -1, -COS_PI_4, 0, COS_PI_4};

	vector<double> b;
	b.push_back(1);			// b[0] = 1
	
	vector<double> a;
	a.push_back(1);			// a[0] = 1
	
	vector<double> sum;
	sum.push_back(1);		// sum[0] = 1

	vector<double> eps;
	
	double x;
	double alpha;

	cin >> x >> alpha;

	if ((alpha - (int)alpha) == 0) { // Z

		//if (a.size()))

		for (int i = 0; i <= alpha - 1; ++i) {

			
			
			b.push_back( b[i] * sqrt(2)*x/(i + 1) );		// b[i+1] = b[i]*( sqrt(2)*x/(i + 1) )

			a.push_back( b[i+1] * cosine_pi_4[(i + 1) % 8] );	// a[i+1] = b[i+1]*cos((i+1)*pi/4)
			
			sum.push_back( sum[i] + a[i+1] );				// sum[i+1] = sum[i] + a[i+1]

			eps.push_back( abs(a[i+1]/sum[i]) );			// eps[i] = abs(a[i+1]/sum[i])

			cout << setprecision(15) << i << '\t' << a[i] << '\t' << sum[i] << '\t' << eps[i] << endl;

			


		}
		
		cout << cosine_pi_4[10 % 8]; // cos(M_PI_4*10)
	}

	system("pause");
	return 0;
}