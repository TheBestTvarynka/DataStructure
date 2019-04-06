#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node
{
	int Value;
	Node *Next;
	Node *Prev;
};

class deck
{
	Node *Head, *Tail;
public:
	deck();
	void push_front(int );
	void push_back(int );
	bool pop_front(int &);
	bool pop_back(int &);
	int size();
	bool isEmpty();
	void print();
	~deck();
};

deck::deck()
{
	Head = new Node;
	Tail = new Node;
	Head->Next = Tail;
	Head->Prev = NULL;
	Tail->Next = NULL;
	Tail->Prev = Head;
}
deck::~deck()
{
	Node *t = Head->Next, *p;

	delete Head;
	while (t != Tail)
	{
		p = t;
		t = t->Next;
		delete p;
	}
	delete Tail;
}
void deck::push_front(int item)
{
	Node *t = new Node;
	t->Value = item;
	t->Next = Head->Next;
	t->Prev = Head;
	Head->Next = t;
	(t->Next)->Prev = t;
}
void deck::push_back(int item)
{
	Node *t = new Node;
	t->Value = item;
	t->Next = Tail;
	t->Prev = Tail->Prev;
	Tail->Prev = t;
	(t->Prev)->Next = t;
}
bool deck::pop_front(int &out)
{
	if (isEmpty())
	{
		cout << "Error: deck is empty..." << endl;
		return false;
	}
	Node *t = Head->Next;
	out = t->Value;
	Head->Next = t->Next;
	(t->Next)->Prev = Head;
	delete t;
	return true;
}
bool deck::pop_back(int &out)
{
	if (isEmpty())
	{
		// cout << "Error: deck is empty..." << endl;
		return false;
	}
	Node *t = Tail->Prev;
	out = t->Value;
	Tail->Prev = t->Prev;
	(t->Prev)->Next = Tail;
	delete t;
	return true;
}
bool deck::isEmpty()
{
	if (Head->Next == Tail)
		return true;
	return false;
}
int deck::size()
{
	int count = 0;
	Node *t = Head;
	while (t->Next != Tail)
		count++;
	return count;
}
void deck::print()
{
	Node *t = Head->Next;
	// cout << "=============================" << endl;
	while (t != Tail)
	{
		cout << setw(5) << t->Value << " ";
		t = t->Next;
	}
	// cout << endl << "=============================" << endl;
}

void createMatrix(deck *(&Matrix), int size)
{
	Matrix = new deck [size];

	for (int IndxLine = 0; IndxLine < size; IndxLine++)
	{
		for (int IndxColumn = 0; IndxColumn < size; IndxColumn++)
		{
			if (IndxColumn % 2 == 0)
				Matrix[IndxLine].push_back(rand() % 101 - 50);
			else
				Matrix[IndxLine].push_front(rand() % 101 - 50);
		}
		Matrix[IndxLine].print();
		cout << endl;
	}
}
void fillVector(deck *Matrix, int size, deck &v)
{
	int value;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
			Matrix[i].pop_front(value);
		v.push_back(value);
	}
	cout << endl;
	//v.print();
}
void printVector(int *vector, int size)
{
	for (int i = 0; i < size; i++)
		cout << vector[i] << " ";
	cout << endl;
}
int main()
{
	srand(time(NULL));

	int size = 0;
	deck *Matrix;
	deck vector;

	cout << "Enter size of matrix: ";
	cin >> size;
	createMatrix(Matrix, size);
	fillVector(Matrix, size, vector);
	vector.print();
	
	return 0;
}