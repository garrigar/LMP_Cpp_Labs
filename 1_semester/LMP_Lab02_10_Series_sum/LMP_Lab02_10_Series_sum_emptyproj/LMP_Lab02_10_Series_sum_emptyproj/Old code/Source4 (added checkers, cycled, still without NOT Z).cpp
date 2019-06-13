
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

const int MAX_ACCEPTED_D_LEN = 15;

bool is_correct_double(string input) {						// check for correctness

	int dotcount = 0;
	bool correct = true;									//suppose is correct

	if (input.length() == 0)
		correct = false;									//if input is empty, then it's not correct
	for (int i = 0; (i < input.length()); ++i) {
		if ((isdigit(input[i]) == 0) && (input[i] != '.'))
			correct = false;								//if there's a non-digital char exept '.' , then not correct
		if (input[i] == '.')
			dotcount++;
	}
	if (dotcount >= 2)
		correct = false;									//if there're more than one dot, than not correct
	if (input.length() > MAX_ACCEPTED_D_LEN)
		correct = false;									//if there're 15+ characters, then this couldn't be loaded into double
	return correct;
}

bool is_zero(string input) {							//for correct inputs only
	bool iszero = true;
	for (int i = 0; (i < input.length()); ++i) {
		if ((input[i] != '0') && (input[i] != '.'))
			iszero = false;								//if there's a non-zero char exept '.' , then number is not zero 

	}
	return iszero;
}

bool get_cont_choice(string msg) {					//to continue or not to continue?

	bool correct = false;					//correctness of a command, this variable is actually useless

	string input;

	while (!correct) {

		cout << msg;

		getline(cin, input);

		if (input.length() != 1) {
			correct = false;
		}
		else {
			switch (input[0]) {
			case 'Y': {
				correct = true;
				return true;
			}
			case 'y': {
				correct = true;
				return true;
			}
			case 'N': {
				correct = true;
				return false;
			}
			case 'n': {
				correct = true;
				return false;
			}
			default: {correct = false; }
			}
		}
	}

}

int main() {

	cout << "Series sum" << endl;
	cout << "Please use non-negative real numbers " << MAX_ACCEPTED_D_LEN << " symbols long" << endl;
	
	string input;			//using a string as an input buffer
	//bool choice = false;	//flag for do..while
	
	double x;
	double limit;
	double alpha;

	
	do 
	{
		vector<long long> c;
		c.push_back(1); 		// c[0] = 1
		long long zerobuf = 0;	// 

		vector<double> b;
		b.push_back(1);			// b[0] = 1
	
		vector<double> a;
		a.push_back(1);			// a[0] = 1
	
		vector<double> sum;
		sum.push_back(1);		// sum[0] = 1

		vector<double> eps;		// no push_back(), начальный элемент будет определяться в самом цикле, поэтому по eps будем отслеживать существование нужной строки
	
		cout << "Input x: > ";
		getline(cin, input);
		if (!is_correct_double(input)) 
		{
			cout << "Input error" << endl;
		}
		else 
		{
			x = stod(input);			//string to double
			limit = exp(x)*cos(x);
			
			do 
			{
				cout << "Input alpha: > ";
				getline(cin, input);
				if (!is_correct_double(input)) 
				{
					cout << "Input error" << endl;
				}
				else 
				{
					alpha = stod(input);
					if (is_zero(input) || alpha < 0) 
					{
						cout << "Alpha is not positive, unpossible to solve" << endl;
					}
					else 
					{
						//MAIN LOGIC
						if ((alpha - (int)alpha) == 0) 
						{	// Z

							if (alpha > eps.size())
								for (int i = eps.size(); i <= alpha - 1; ++i) 
								{

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

									a.push_back(b[i + 1] * c[i + 1]);			// a[i+1] = b[i+1]*c[i+1]

									sum.push_back(sum[i] + a[i + 1]);			// sum[i+1] = sum[i] + a[i+1]

																				//eps.push_back( abs(a[i+1]/sum[i]) );		// eps[i] = abs(a[i+1]/sum[i])
									eps.push_back(abs(limit - sum[i]));			// eps[i] = abs(limit - sum[i])

									cout << setprecision(15) << i << '\t' << a[i] << '\t' << sum[i] << '\t' << eps[i] << endl;

								}
							else
							{
								cout << setprecision(15) << alpha << '\t' << a[alpha - 1] << '\t' << sum[alpha - 1] << '\t' << eps[alpha - 1] << endl;
							}
						}
						else
						{
							// NOT Z
						}
						//MAIN LOGIC END
					}

				}

			} while (get_cont_choice("Continue with current x? (Y/N) > "));
			
		}

	} while (get_cont_choice("Continue? (Y/N) > "));
	return 0;
}
