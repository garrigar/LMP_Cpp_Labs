#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void printInto2Streams(ostream &os1, ostream &os2, string msg) // вывод msg в два потока
{ 
	os1 << msg << endl;
	os2 << msg << endl;
}

template<class T> class ArrayFromString { // класс-обертка над массивом, позволяющий создавать его прямо из строки
	int sz;		// число элементов
	T* arr;		// указатель на элементы

public:
	ArrayFromString(string str) // конструктор по строке
	{

		istringstream iss(str);			// строка-поток для анализа и чтения строки

		int n = 0;						// количество элементов

		bool cont = true;				// стоит ли продолжать
		bool ok = true;					// корректна ли строка

		T buf;							// буферная переменная
		while (cont)
		{

			iss >> buf;					// пытаемся считать

			if (iss.fail())				// если состояние fail
			{
				cont = false;				// продолжать не будем
				if (!iss.eof())				// если там что-то оставалось, то строка некорректна
					ok = false;				// (а если, например, строка пустая, то ok = true) 
			}
			else						// если считалось
			{
				char c = iss.peek();		// посмотрим на следующий символ
				if (iss.eof())				// если это был конец
				{
					n++;						// то нашли корректный элемент
					cont = false;				// продолжать не будем
				}
				else						// если не конец
					if (c == ' ')				// то если пробел, то нашли корректный элемент
						n++;
					else						// иначе нет разделителя, и в строке "синтаксическая" ошибка
						ok = cont = false;
			}
		}

		if (!ok)						// если строка некорректна, передаем управление наружу путем исключения
			throw IncorrectStringEx();

		iss.clear();					// сброс ошибок потока
		iss.seekg(0, ios_base::beg);	// "курсор" на начало

		sz = n;							// инициализируем поля
		arr = new T[n];

		for (int i = 0; i < n; ++i)		// считывание элементов
			iss >> arr[i];

	}

	~ArrayFromString() { delete[] arr; }	// деструктор
	
	int size() const { return sz; }
	
	T& operator[](int n) { return arr[n]; }	// возврат ссылки (индексирование)

	struct IncorrectStringEx { };			// исключение, выбрасываемое когда входная строка с массивом некорректна
};

struct IncorrectParamEx {};			// исключение при некорректном параметре d
struct IncorrectFileFormatEx {};	// исключение при некорректном формате файла

void calc(ArrayFromString<double> &a, double d, double &result, bool &nomatch) // функция, обрабатывающая массив
{
	nomatch = true;			// переменная-флаг, true если в строке нет элементов, удовлетворяющих условию
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

	ifstream fin("input.txt");		// входной файл

	if (!fin.is_open())
	{
		cout << "Couldn't open the file" << endl;
		system("pause");
		return 1;
	}

	ofstream fout("output.txt");	// выходной файл

	try 
	{
		string arrstr;
		getline(fin, arrstr);		// считывание строки с массивом и передача ее в конструктор
		ArrayFromString<double> a(arrstr);
		
		double d;
		if (!(fin >> d))			// считывание параметра с одновременной проверкой корректности 
			throw IncorrectParamEx();
		
		char ch;		// проверка, есть ли после параметра еще что-то, т.е. обработка других форматов входных файлов
		while ((ch = fin.get()) != EOF)
			if (!isspace(ch))
				throw IncorrectFileFormatEx(); // если есть что-то кроме пробела, то формат файла некорректен
		
		double result;
		bool nomatch;				// переменная-флаг, true если в строке нет элементов, удовлетворяющих условию
		calc(a, d, result, nomatch);
		
		if (a.size() == 0)			// если массив пуст
			printInto2Streams(cout, fout, "Empty array, couldn't calculate");
		else 
		{
			cout << "Array: ";		 // вывод массива
			for (int i = 0; i < a.size(); ++i)
				cout << a[i] << ' ';
			cout << '\n';
			
			cout << "Result: ";		// вывод результата
			if (nomatch) 
				printInto2Streams(cout, fout, "undefined (no matches found)");	 // undefined если nomatch
			else 
			{
				cout << result << '\n';
				fout << result << '\n';
			}

		}
	}
	catch (ArrayFromString<double>::IncorrectStringEx e) 
	{
		printInto2Streams(cout, fout, "Incorrect array format!");		// ругаемся на некорректный массив
	}
	catch (IncorrectParamEx e)
	{
		printInto2Streams(cout, fout, "Incorrect parameter format!");	// ругаемся на некорректный параметр
	}
	catch (IncorrectFileFormatEx e)
	{
		printInto2Streams(cout, fout, "Incorrect file format!");		// ругаемся на некорректнвый формат файла
	}
	fin.close();
	fout.close();

	system("pause");
	return 0;
}