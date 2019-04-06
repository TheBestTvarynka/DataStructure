#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

class deck
{
	int *array;
	int capasity, top, bottom, size;
public:
	deck();
	void push_front(int );
	void push_back(int );
	bool pop_front(int &);
	bool pop_back(int &);
	void resize(int );
	int Size();
	bool isEmpty();
	void print();
	~deck();
};

deck::deck()
{
	capasity = 5;
	array = new int[capasity];
	size = top = bottom = 0;
}
deck::~deck()
{
	top = bottom = size = capasity = 0;
	// delete [] array;
}
void deck::push_back(int item)
{
	array[top++] = item;
	top = top % capasity;
	size++;
	if (size == capasity)
		resize(capasity * 2);
}
void deck::push_front(int item)
{
	array[--bottom] = item;
	bottom = bottom % capasity;
	size++;
	if (size == capasity)
		resize(capasity * 2);
}
bool deck::pop_back(int &out)
{
	if (isEmpty())
	{
		cout << "Error: deck is empty" << endl;
		return false;
	}
	out = array[--top];
	top = top % capasity;
	size--;
	if (size <= capasity / 4)
		resize(capasity / 2);
	return true;
}
bool deck::pop_front(int &out)
{
	if (isEmpty())
	{
		cout << "Error: deck is empty" << endl;
		return false;
	}
	out = array[bottom++];
	bottom = bottom % capasity;
	size--;
	if (size <= capasity / 4)
		resize(capasity / 2);
	return true;
}
void deck::resize(int newCapasity)
{
	int *newArray = new int[newCapasity];
	int s, f, p;
	if (top <= bottom)
	{
		f = capasity;
		s = top;
	}
	else
	{
		s = 0;
		f = top;
	}
	for (int i = bottom; i < f; i++)
		newArray[i - bottom] = array[i];
	p = f - bottom;
	for (int j = 0; j < s; j++)
		newArray[p + j] = array[j];
	bottom = 0;
	top = p + s;
	capasity = newCapasity;
	// delete array;
	array = newArray;
}
bool deck::isEmpty()
{
	if (top == bottom)
		return true;
	return false;
}
int deck::Size()
{
	return size;
}
void deck::print()
{
	int i = bottom;
	// cout << "=============================" << endl;
	while (i != top && i != capasity)
	{
		cout << setw(5) << array[i] << " ";
		i++;
	}
	if (i != top)
	{
		for (int j = 0; j < top; j++)
			cout << setw(5) << array[j] << " ";
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