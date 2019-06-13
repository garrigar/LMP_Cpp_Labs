#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/*
const char EOLN = '\n';
const std::string SKIP_CHARACTERS = " ";
const std::string INCORRECT_MESSAGE = "Input is incorrect. Try again>";
void ClearInputStream(std::istream &in)
{
	in.clear();
	while (in.peek() != EOLN && in.peek() != EOF)
	{
		in.get();
	}
}
int Seek(std::istream &in)
{
	while (in.peek() != EOLN &&
		SKIP_CHARACTERS.find((char)in.peek()) != std::string::npos)
	{
		in.get();
	}
	return in.peek();
}
double ReadFloat(std::istream &in)
{

	double ans;
	in >> ans;
	while (!in || Seek(in) != EOLN)
	{
		ClearInputStream(in);
		std::cout << INCORRECT_MESSAGE;
		in >> ans;
	}
	return ans;
}

/
fin >> n;
if (fin.fail())
	throw IncorrectDataExeption();
/

const int MAX_ACCEPTED_D_LEN = 15;
bool is_correct_double(string input) {						// check for correctness
	
	int dotcount = 0;
	bool correct = true;									//suppose is correct
	
	if (input.length() == 0) 
		correct = false;									//if input is empty, then it's not correct
	for (int i = 0; (i < input.length()); ++i) {
		if ( (isdigit(input[i]) == 0) && (input[i] != '.') ) 
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

stod

*/

double get_eps()		// finds machine epsilon
{
	double eps = 1.0;
	while (1.0 + eps != 1.0)
	{
		eps /= 2.0;
	}
	return eps;
}
	
class DivByZeroEx { };				// exeption

double calc(double a, double b) 
{
	double EPS = get_eps();				// machine epsilon

	if (abs(a - b) < EPS)				// if equal
	{
		return ((b == 0) ? 0 : (-b));	// if b exactly equals 0, returning 0 instead of -0, otherwise returning -b
	}
	else if (a < b) 
	{
		return (a - b) / 3;
	}
	else if (b < a) 
	{
		if (abs(a) < EPS)				// if a equals 0, division is not possible
			throw DivByZeroEx();
		else
			return (b + 5) / a + 1;
	}
	else 
	{
		//??? WTF case
	}
}

int main() 
{

	ifstream fin("input.txt");

	if (!fin.is_open()) 
	{
		cout << "Couldn't open the file" << endl;
		system("pause");
		return 1;
	}

	ofstream fout("output.txt");

	double a, b;

	while (fin >> a >> b) // while (!fin.fail())
	{
		//fin >> a >> b;
		//if (!fin.fail())
		
		cout << fixed << setprecision(6) << "a = " << a << "\tb = " << b << "\t";

		try
		{
			double x = calc(a, b);
			cout << fixed << setprecision(6) << "X = " << x << "\n";
			fout << fixed << setprecision(6) << x << "\n";
		}
		catch (DivByZeroEx e)						// catching division by 0
		{
			cout << "X is undefined (div by 0)\n";
			fout << "undefined (div by 0)\n";
		}
		
	}
	fin.close();
	fout.close();

	system("pause");
	return 0;
}
