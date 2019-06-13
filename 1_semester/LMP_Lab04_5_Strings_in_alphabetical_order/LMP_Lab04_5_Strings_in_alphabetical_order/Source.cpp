#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void insertionSort(vector<string>& a) { 
	int len = a.size();
	int last;
	string tmp;
	for (int i = 1; i < len; ++i) { 
		tmp = a[i]; 
		for (last = i; last > 0 && a[last-1][0] > tmp[0]; --last) 
			a[last] = a[last-1];	
		a[last] = tmp; 
	} 
}

int main(){

	vector<string> arr;

	ifstream fin("input.txt");
	string str;

	ofstream fout("output.txt");

	if ( !fin.is_open() ) {
		cout << "Can't open file" << endl;
		system("pause");
		return 1;
	}
	while ( !fin.eof() ){
		getline(fin, str);
		arr.push_back(str);
	}
	fin.close();

	insertionSort(arr);

	for (int i = 0; i < arr.size(); ++i)
	{
		fout << arr[i] << endl;
	}
	fout.close();

	return 0;
}