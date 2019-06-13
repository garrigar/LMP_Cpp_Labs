#include <iostream>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

const int MAX_OUT = 50;		// max print value

const int GAP = 2;			// for almost sorted -- max gap between swapped elements (recommended 1 or 2)

double randDouble()			// random double
{
	return (rand() / 100.0);
}

class LinkedList {		// single linked list class
private:
	
	struct Node			// node
	{
		Node *next;		// pointer to next
		double value;	// key
	};

	Node *head;			// first node

	int length;			// number of elements

	// quicksort a linked list
	void quickSort_node(Node *&root, int len)
	{
		// trivial lists are returned immediately
		if (!root || !(root->next))
			return;

		Node *leftPartHead = nullptr, **pp_lpCur = &leftPartHead;	// ** is a pointer to a node pointer
																	// it means where we will put another node
																	// makes appending easier
		Node *rightPartHead = nullptr, **pp_rpCur = &rightPartHead;
		Node *centerPartHead = nullptr, **pp_cpCur = &centerPartHead;

		Node *buf = root;									// future pivot node
		for (int i = 0; i < len / 2; ++i, buf = buf->next); // getting pivot value from center
		double pvt = buf->value;

		int lpLen = 0, rpLen = 0, cpLen = 0;				// future lengths of parts

		while (root)					// iterating thru the list
		{
			if (root->value == pvt)		// if exactly equal
			{
				*pp_cpCur = root;		// tack (add) on center list end
				pp_cpCur = &(*pp_cpCur)->next;
				cpLen++;
			}
			else if (root->value < pvt)
			{
				*pp_lpCur = root;		// tack (add) on left list end
				pp_lpCur = &(*pp_lpCur)->next;
				lpLen++;
			}
			else
			{
				*pp_rpCur = root;		// tack (add) on right list end
				pp_rpCur = &(*pp_rpCur)->next;
				rpLen++;
			}
			root = root->next;
		}

		// terminate all lists, need to have NULL on end 
		*pp_lpCur = *pp_cpCur = *pp_rpCur = nullptr;
		
		// sort sublists
		quickSort_node(leftPartHead, lpLen);
		quickSort_node(rightPartHead, rpLen);

		// find end of lhs list, slip the pivot into  position, then 
		// tack on the rhs list.

		while (*pp_lpCur)			// find end of left
			pp_lpCur = &(*pp_lpCur)->next;
		*pp_lpCur = centerPartHead; // append center

		while (*pp_lpCur)			// find end of center
			pp_lpCur = &(*pp_lpCur)->next;

		*pp_lpCur = rightPartHead;	// append right

		// set final output
		root = leftPartHead;
		
	}

public:

	LinkedList()	// constructor
	{
		head = nullptr;
		length = 0;
	}

	~LinkedList() {
		Node *cur = head;

		while (cur) {              // iterate over all elements
			Node *tmp = cur;
			cur = tmp->next;     // save pointer to the next element
			delete tmp;       // delete the current entry
		}
	}

	void prependValue(double d) {
		Node *n = new Node(); // create node
		n->value = d;
		n->next = head;

		head = n;			// move head

		length++;
	}

	void print(ostream& os) { // prints elements, max -- MAX_OUT
		int i = 0;
		for (Node *cur = head; cur && i <= MAX_OUT; cur = cur->next, ++i) {
			os << setprecision(10) << cur->value << ' ';
			if (i == MAX_OUT) cout << "...";
		}
		os << '\n';
	}

	void quickSort() {			// calls quicksort for head
		quickSort_node(head, length);
	}

	void fillRandom(int len) {	// fills random
		for (int i = 0; i < len; i++)
		{
			prependValue(randDouble());
		}
	}

	void fillAlmostSorted(int len) {
		vector<double> v;
		v.push_back(randDouble());
		for (int i = 1; i < len; i++) // creating sorted vector
		{
			v.push_back(v[i - 1] + randDouble());
		}
		int i = 0;
		int g;
		while (i + GAP < len) // swapping elements
		{
			g = 1 + rand() % GAP;
			swap(v[i], v[i + g]);
			i += (g + 1);
		}

		for (int i = len - 1; i >= 0; --i) // prepending values
		{
			prependValue(v[i]);
		}

	}

	void fillReversed(int len) { // fills reversed
		double val = randDouble();
		for (int i = 0; i < len; i++) {
			prependValue(val);
			val += randDouble();
		}
	}
};

int main()
{
	cout << "Quick3 sort" << endl;
	srand(time(0));

	int n;

	// -- for time count --
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);
	double time_rnd, time_almost, time_rev; // in seconds
	// ------

	cout << "Input number of elements: > ";
	cin >> n;

	//---------------------------------
	LinkedList llRandom;	// list for random
	llRandom.fillRandom(n); // filling
	cout << "Random:\n";
	llRandom.print(cout);	// printing
	
	QueryPerformanceCounter(&start);
	llRandom.quickSort();
	QueryPerformanceCounter(&finish);
	time_rnd = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart; // calc time
	
	cout << "Sorted random:\n";
	llRandom.print(cout);
	cout << "Time: " << time_rnd << " sec" << endl;
	//----------------------------------
	cout << endl;
	//---------------------------------- // same thing for almost sorted
	LinkedList llAlmSorted;
	llAlmSorted.fillAlmostSorted(n);
	cout << "Almost sorted:\n";
	llAlmSorted.print(cout);

	QueryPerformanceCounter(&start);
	llAlmSorted.quickSort();
	QueryPerformanceCounter(&finish);
	time_almost = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;

	cout << "Sorted almost sorted:\n";
	llAlmSorted.print(cout);
	cout << "Time: " << time_almost << " sec" << endl;
	//----------------------------------
	cout << endl;
	//---------------------------------- // same thing for reversed
	LinkedList llReversed;
	llReversed.fillReversed(n);
	cout << "Reversed:\n";
	llReversed.print(cout);

	QueryPerformanceCounter(&start);
	llReversed.quickSort();
	QueryPerformanceCounter(&finish);
	time_rev = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;

	cout << "Sorted reversed:\n";
	llReversed.print(cout);
	cout << "Time: " << time_rev << " sec" << endl;
	//----------------------------------
	
	cout << endl;
	system("pause");
}