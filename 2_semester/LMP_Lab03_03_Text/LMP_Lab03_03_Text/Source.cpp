#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int MAX_LEN = 6;					// ������������ ����� �����

bool istPassend(const string& word)		// �������, ����������� �������� �� ����� ��� �������
{
	int len = word.size();
	if (len > MAX_LEN) return false;	// ���� ����� ������, ����� �����������

	bool withLetter = false;			// ����������� �� � ����� �����
	bool withNumber = false;			// ����������� �� � ����� �����
	for (int i = 0; i < len; i++)
	{
		if (isalpha(word[i]))		// ���� �����, ���������� ����
			withLetter = true;
		else if (isdigit(word[i]))	// ���� �����, ���������� ����
			withNumber = true;
		else
			return false;			// ����� ������ �� �� ����������, � ����� �����������
	}
	return (withLetter && withNumber);		// ����� ���������, ����� � ��� ����������� � �����, � �����
}

void readAllText(ifstream& fin, stringstream& text) // ��������� �� �� fin � text
													// �������� � ������� ����� stringstream, 
													// ��� ����������, ���������, reusable
{
	text << fin.rdbuf(); /* rdbuf() just returns a pointer to the underlying basic_streambuf object 
							for the given [io]stream object.
							basic_ostream<...> has an overload for operator<< for a pointer to basic_streambuf<...> 
							which writes out the contents of the basic_streambuf<...>.
							*/
}

void findWords(stringstream& text, vector<string>& words) // ������ text �� �����, �����������, ��������� ���������� � ans
{
	string buf;						// �������� ������
	while (text >> buf)
		if (istPassend(buf))
			words.push_back(buf);	// ���� ���������� ������, ���� ����� ���������, ��������� � �����

	// ����� ��� ����������, ����� ����� ���� �� ����� �������� � text
	text.clear();					// ����� ������ ������
	text.seekg(0, ios_base::beg);	// "������" �� ������
};

void printAllText(ostream& os, const stringstream& text)	// �������� ���������� ������ � os
{
	os << text.str();		// os << (���� �����)
}

void printWords(ostream& os, const vector<string>& words, const char terminator)	// �������� ����� �� words � os 
																					// � ������������ terminator
{
	for (const string& word : words)	// ���� foreach
		os << word << terminator;
}

int main()
{
	ifstream fin("input.txt");		// ������� ����

	if (!fin.is_open())				// ���� ���� �� ������, �� �������� � �� ����������
	{
		cout << "Couldn't open the file" << endl;
		system("pause");
		return 1;
	}

	stringstream text;			// ���� �����
	readAllText(fin, text);		// ������ �����

	fin.close();


	vector<string> ans;			// ������ ���������� ����
	findWords(text, ans);		// ���������

	cout << "Original text:\n";		// �������� ������������ �����
	printAllText(cout, text);

	cout << "\nCorrect words:\n";	// �������� ���������� �����
	printWords(cout, ans, ' ');

	cout << endl;
	system("pause");
	return 0;
}
