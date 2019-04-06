#include <iostream>

using namespace std;

struct Node
{
	int Value;
	Node *Next;
};

class queue
{
	Node *Head, *Tail;
public:
	queue();
	~queue();
	void push(int );
	bool pop(int &);
	bool isEmpty();
	int size();
	void print();
};
queue::queue()
{
	Head = new Node;
	Head->Next = NULL;
	Tail = Head;
}
queue::~queue()
{
	Node *t = Head->Next;
	Node *p = Head;
	delete p;
	while (t != NULL)
	{
		p = t;
		t = t->Next;
		delete p;
	}
}
void queue::push(int item)
{
	Node *t = new Node;
	t->Value = item;
	t->Next = NULL;
	Tail->Next = t;
	Tail = t;
}
bool queue::pop(int &out)
{
	if (isEmpty())
		return false;
	Node *t = Head->Next;
	out = t->Value;
	Head->Next = t->Next;
	delete t;
	return true;
}
bool queue::isEmpty()
{
	if (Head->Next == NULL)
		return true;
	return false;
}
int queue::size()
{
	Node *t = Head->Next;
	int count = 0;
	while (t != NULL)
	{
		count++;
		t = t->Next;
	}
	return count;
}
void queue::print()
{
	Node *t = Head->Next;
	while (t != NULL)
	{
		cout << t->Value << " ";
		t = t->Next;
	}
	cout << endl;
}

int main()
{
	queue A;
	int a;

	A.push(5);
	A.push(9);
	A.push(1);
	A.push(7);
	A.print();

	A.pop(a);
	cout << a << endl;
	A.pop(a);
	cout << a << endl;
	A.print();

	cin >> a;
	A.push(6);
	A.push(12);
	A.print();

	cin >> a;
	A.pop(a);
	cout << a << endl;
	A.print();

	cin >> a;
	cout << A.size() << endl;
	return 0;
}