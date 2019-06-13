
#define _USE_MATH_DEFINES  

#include <cmath>
#include <vector>
#include <iostream>

#include <iomanip>

using namespace std;


int main()
{
	
	vector<long long> c;
	c.push_back(1); 			// c[0] = 1
	
	int alpha;

	cin >> alpha;

		int rem = 0;
		long long zerobuf = 0;
		for (int i = 0; i <= alpha - 1; ++i) {
			rem = i % 4;
			if (rem == 0)
				c.push_back( c[i] );
			if (rem == 1) {
				zerobuf = c[i]*(-2);
				c.push_back( 0 );
				}
			if (rem == 2)
				c.push_back( zerobuf );
			if (rem == 3)
				c.push_back( c[i]*2 );
				
			cout << i << '\t' << c[i] << endl;
			
		}


	return 0;
}