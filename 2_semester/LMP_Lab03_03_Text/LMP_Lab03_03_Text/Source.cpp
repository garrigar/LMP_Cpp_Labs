#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int MAX_LEN = 6;					// максимальная длина слова

bool istPassend(const string& word)		// функция, проверяющая подходит ли слово под условие
{
	int len = word.size();
	if (len > MAX_LEN) return false;	// если длина больше, слово некорректно

	bool withLetter = false;			// встретилась ли в слове буква
	bool withNumber = false;			// встретилась ли в слове цифра
	for (int i = 0; i < len; i++)
	{
		if (isalpha(word[i]))		// если буква, активируем флаг
			withLetter = true;
		else if (isdigit(word[i]))	// если цифра, активируем флаг
			withNumber = true;
		else
			return false;			// иначе символ не из допустимых, и слово некорректно
	}
	return (withLetter && withNumber);		// слово корректно, когда в нем встретились и буква, и цифра
}

void readAllText(ifstream& fin, stringstream& text) // считывает всё из fin в text
													// работаем с текстом через stringstream, 
													// это оптимально, компактно, reusable
{
	text << fin.rdbuf(); /* rdbuf() just returns a pointer to the underlying basic_streambuf object 
							for the given [io]stream object.
							basic_ostream<...> has an overload for operator<< for a pointer to basic_streambuf<...> 
							which writes out the contents of the basic_streambuf<...>.
							*/
}

void findWords(stringstream& text, vector<string>& words) // парсит text на слова, анализирует, добавляет корректные в ans
{
	string buf;						// буферная строка
	while (text >> buf)
		if (istPassend(buf))
			words.push_back(buf);	// пока получается читать, если слово корректно, добавляем в ответ

	// чисто для кошерности, чтобы можно было БЫ потом работать с text
	text.clear();					// сброс ошибок потока
	text.seekg(0, ios_base::beg);	// "курсор" на начало
};

void printAllText(ostream& os, const stringstream& text)	// печатает содержимое текста в os
{
	os << text.str();		// os << (весь текст)
}

void printWords(ostream& os, const vector<string>& words, const char terminator)	// печатает слова из words в os 
																					// с разделителем terminator
{
	for (const string& word : words)	// цикл foreach
		os << word << terminator;
}

int main()
{
	ifstream fin("input.txt");		// входной файл

	if (!fin.is_open())				// если файл не открыт, то ругаемся и не продолжаем
	{
		cout << "Couldn't open the file" << endl;
		system("pause");
		return 1;
	}

	stringstream text;			// весь текст
	readAllText(fin, text);		// читаем текст

	fin.close();


	vector<string> ans;			// вектор корректных слов
	findWords(text, ans);		// заполняем

	cout << "Original text:\n";		// печатаем оригинальный текст
	printAllText(cout, text);

	cout << "\nCorrect words:\n";	// печатаем корректные слова
	printWords(cout, ans, ' ');

	cout << endl;
	system("pause");
	return 0;
}
