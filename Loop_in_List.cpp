#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

struct Node
{
	int Value;
	Node *Next;
};

class List
{
	Node *Main;
	Node *Position;
public:
	List()
	{
		Main = new (Node);
		Main->Next = NULL;
		Position = Main;
	};
	Node *SearchLoop();
	void Print();
	void Build();
	Node *ReturnElement(int);
	void ClearList();
};

int main()
{
	List Example;
	Node *Loop;
	Example.Build();
	Loop = Example.SearchLoop();
	if (Loop == NULL)
	{
		cout << "Loop not found." << endl;
		Example.Print();
	}
	else
		cout << "Loop found! Element: " << Loop->Value << endl;

	// Example.ClearList();
	// ClearList - у тому випадку якщо немає циклу
	return 0;
}

Node *List::SearchLoop()
{
	Node *FirstPoint = Main->Next, *SecondPoint = Main->Next;

	do
	{
		FirstPoint = FirstPoint->Next;
		SecondPoint = (SecondPoint->Next)->Next;
	}
	while (FirstPoint != SecondPoint && SecondPoint != NULL);
		
	if (SecondPoint == NULL)
		return NULL;
	
	FirstPoint = Main->Next;
	while (FirstPoint != SecondPoint)
	{
		FirstPoint = FirstPoint->Next;
		SecondPoint = SecondPoint->Next;
	}
	return SecondPoint;
}
void List::Build()
{
	int a = 1;
	char v = 'n';
	Node *t = Position;

	while (a != 0 && v != 'c')
	{
		cout << "You want add new element or connect with exist element? (n/c): ";
		cin >> v;
		cout << "Enter element: ";
		cin >> a;

		t->Next = new (Node);
		if (v == 'c')
			t->Next = ReturnElement(a);
		else
		{
			t = t->Next;
			t->Next = NULL;
			t->Value = a;
		}
	}
	Position = t;
}
void List::Print()
{
	Node *t;
	t = Main;
	t = t->Next;
	while (t != NULL)
	{
		cout << t->Value << " ";
		t = t->Next;
	}
	cout << endl;
}
Node *List::ReturnElement(int Index)
{

	Node *t = Main->Next;
	while (t->Value != Index)
		t = t->Next;
	return t;
}
void List::ClearList()
{
	Node *t = Main, *next = t;
	while (t != NULL)
	{
		next = t->Next;
		delete t;
		t = next;
	}
}