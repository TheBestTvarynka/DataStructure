#include <iostream>

using namespace std;

class queue
{
	int *Array;
	int top, bottom, size, capasity;
public:
	queue(int);
	void push(int);
	bool pop(int &);
	int Size();
	void resize(int );
	bool isEmpty();
	void print();
	~queue();
};
queue::queue(int Capasity = 5)
{
	capasity = Capasity;
	Array = new int[capasity];
	top = bottom = size = 0;
}
queue::~queue()
{
	top = bottom = size = 0;
	delete [] Array;
}
void queue::push(int item)
{
	if (size == capasity)
		resize(capasity * 2);
	Array[top++] = item;
	size++;
	top = top % capasity;
}
bool queue::pop(int &out)
{
	if (isEmpty())
		return false;
	if (size < capasity / 4)
		resize(capasity / 2);
	out = Array[bottom++];
	size--;
	bottom = bottom % capasity;
	return true;
}
void queue::resize(int newCapasity)
{
	int *newArray = new int[newCapasity];
	int f, s, p = 0;
	if (top <= bottom)
	{
		f = capasity;
		s = top;
	}
	else
	{
		f = top;
		s = 0;
	}
	for (int i = bottom; i < f; i++)
	{
		newArray[p] = Array[i];
		p++;
	}
	for (int j = 0; j < s; j++)
	{
		newArray[p] = Array[j];
		p++;
	}
	capasity = newCapasity;
	bottom = 0;
	top = size;
	delete Array;
	Array = newArray;
}
bool queue::isEmpty()
{
	if (size == 0)
		return true;
	return false;
}
int queue::Size()
{
	return size;
}
void queue::print()
{
	int i = bottom;
	while (i != top && i != capasity)
	{
		cout << Array[i] << " ";
		i++;
	}
	if (i == capasity)
	{
		for (int j = 0; j < top; j++)
			cout << Array[j] << " ";
	}
	cout << endl;
}

void pps(queue &q)
{
	int a = 1;

	cin >> a;
	while (a != 0)
	{
		q.push(a);
		cin >> a;
	}
	q.print();
}
void ppo(queue &q)
{
	int a = 1;
	cin >> a;
	while (a != 1)
	{
		q.pop(a);
		cout << "> " << a << endl;
		cin >> a;
	}
	q.print();
}
int main()
{
	queue Qu;
	
	pps(Qu);
	ppo(Qu);
	pps(Qu);
	return 0;
}