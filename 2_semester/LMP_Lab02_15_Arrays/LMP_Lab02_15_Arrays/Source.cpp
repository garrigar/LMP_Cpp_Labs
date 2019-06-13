#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void printInto2Streams(ostream &os1, ostream &os2, string msg) // ����� msg � ��� ������
{ 
	os1 << msg << endl;
	os2 << msg << endl;
}

template<class T> class ArrayFromString { // �����-������� ��� ��������, ����������� ��������� ��� ����� �� ������
	int sz;		// ����� ���������
	T* arr;		// ��������� �� ��������

public:
	ArrayFromString(string str) // ����������� �� ������
	{

		istringstream iss(str);			// ������-����� ��� ������� � ������ ������

		int n = 0;						// ���������� ���������

		bool cont = true;				// ����� �� ����������
		bool ok = true;					// ��������� �� ������

		T buf;							// �������� ����������
		while (cont)
		{

			iss >> buf;					// �������� �������

			if (iss.fail())				// ���� ��������� fail
			{
				cont = false;				// ���������� �� �����
				if (!iss.eof())				// ���� ��� ���-�� ����������, �� ������ �����������
					ok = false;				// (� ����, ��������, ������ ������, �� ok = true) 
			}
			else						// ���� ���������
			{
				char c = iss.peek();		// ��������� �� ��������� ������
				if (iss.eof())				// ���� ��� ��� �����
				{
					n++;						// �� ����� ���������� �������
					cont = false;				// ���������� �� �����
				}
				else						// ���� �� �����
					if (c == ' ')				// �� ���� ������, �� ����� ���������� �������
						n++;
					else						// ����� ��� �����������, � � ������ "��������������" ������
						ok = cont = false;
			}
		}

		if (!ok)						// ���� ������ �����������, �������� ���������� ������ ����� ����������
			throw IncorrectStringEx();

		iss.clear();					// ����� ������ ������
		iss.seekg(0, ios_base::beg);	// "������" �� ������

		sz = n;							// �������������� ����
		arr = new T[n];

		for (int i = 0; i < n; ++i)		// ���������� ���������
			iss >> arr[i];

	}

	~ArrayFromString() { delete[] arr; }	// ����������
	
	int size() const { return sz; }
	
	T& operator[](int n) { return arr[n]; }	// ������� ������ (��������������)

	struct IncorrectStringEx { };			// ����������, ������������� ����� ������� ������ � �������� �����������
};

struct IncorrectParamEx {};			// ���������� ��� ������������ ��������� d
struct IncorrectFileFormatEx {};	// ���������� ��� ������������ ������� �����

void calc(ArrayFromString<double> &a, double d, double &result, bool &nomatch) // �������, �������������� ������
{
	nomatch = true;			// ����������-����, true ���� � ������ ��� ���������, ��������������� �������
	result = 1.0;
	for (int i = 0; i < a.size(); ++i)
		if (a[i] < 0 && ( ( abs(a[i] - d) < DBL_EPSILON) || a[i] < d) )
		{
			nomatch = false;
			result *= a[i];
		}
}

int main()
{

	ifstream fin("input.txt");		// ������� ����

	if (!fin.is_open())
	{
		cout << "Couldn't open the file" << endl;
		system("pause");
		return 1;
	}

	ofstream fout("output.txt");	// �������� ����

	try 
	{
		string arrstr;
		getline(fin, arrstr);		// ���������� ������ � �������� � �������� �� � �����������
		ArrayFromString<double> a(arrstr);
		
		double d;
		if (!(fin >> d))			// ���������� ��������� � ������������� ��������� ������������ 
			throw IncorrectParamEx();
		
		char ch;		// ��������, ���� �� ����� ��������� ��� ���-��, �.�. ��������� ������ �������� ������� ������
		while ((ch = fin.get()) != EOF)
			if (!isspace(ch))
				throw IncorrectFileFormatEx(); // ���� ���� ���-�� ����� �������, �� ������ ����� �����������
		
		double result;
		bool nomatch;				// ����������-����, true ���� � ������ ��� ���������, ��������������� �������
		calc(a, d, result, nomatch);
		
		if (a.size() == 0)			// ���� ������ ����
			printInto2Streams(cout, fout, "Empty array, couldn't calculate");
		else 
		{
			cout << "Array: ";		 // ����� �������
			for (int i = 0; i < a.size(); ++i)
				cout << a[i] << ' ';
			cout << '\n';
			
			cout << "Result: ";		// ����� ����������
			if (nomatch) 
				printInto2Streams(cout, fout, "undefined (no matches found)");	 // undefined ���� nomatch
			else 
			{
				cout << result << '\n';
				fout << result << '\n';
			}

		}
	}
	catch (ArrayFromString<double>::IncorrectStringEx e) 
	{
		printInto2Streams(cout, fout, "Incorrect array format!");		// �������� �� ������������ ������
	}
	catch (IncorrectParamEx e)
	{
		printInto2Streams(cout, fout, "Incorrect parameter format!");	// �������� �� ������������ ��������
	}
	catch (IncorrectFileFormatEx e)
	{
		printInto2Streams(cout, fout, "Incorrect file format!");		// �������� �� ������������� ������ �����
	}
	fin.close();
	fout.close();

	system("pause");
	return 0;
}