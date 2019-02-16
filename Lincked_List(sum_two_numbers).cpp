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
		Main = new Node;
		Main->Next = NULL;
		Position = Main;
	};
	void Print()
	{
		Node *t;
		t = Main->Next;
		while (t != NULL)
		{
			cout << t->Value << " ";
			t = t->Next;
		}
		cout << endl;
	}
	void Push(int Value)
	{
		Node *t;
		t = Position;
		t->Next = new Node;
		t = t->Next;
		t->Value = Value;
		t->Next = NULL;
		Position = t;
	}
	int Pop()
	{
		int e;
		Node *t;
		Node *p;
		t = Main->Next;
		if (t == NULL)
			return 0;
		p = t->Next;
		e = t->Value;
		delete t;
		Main->Next = p;
		return e;
	}
	int is_empty()
	{
		Node *t;
		t = Main->Next;
		if (t == NULL) return false;
		else return true;
	}
	int Size()
	{
		int size = 0;
		Node *t = Main;
		while (t->Next != NULL)
		{
			t = t->Next;
			size++;
		}
		return size;
	}
	void Cear()
	{
		Node *Item = Main->Next, *Next;
		while (Item != NULL)
		{
			Next = Item->Next;
			delete Item;
			Item = Next;
		}
		Main->Next = NULL;
		Position = Main;
	}
};

void Sum1(List &A, List &B, List &C)
{
	int sum, rem = 0;
	while (A.is_empty() || B.is_empty())
	{
		sum = A.Pop() + B.Pop();
		C.Push((sum + rem) % 10);
		rem = (int)((sum + rem) / 10);
	}
	if (rem == 1)
		C.Push(1);
}

void Sum2(List &A, List &B, List &C)
{
	int First = 0, Second = 0, Result;
	int n, n1;

	n = A.Size();
	for (int i = 1; i <= n; i++)
		First += A.Pop() * pow(10, (n - i));

	n1 = B.Size();
	for (int j = 1; j <= n1; j++)
		Second += B.Pop() * pow(10, (n1 - j));
	
	Result = First + Second;
	
	if (n < n1)
		n = n1;
	if (Result >= pow(10, n))
		n++;
	
	for (int l = n - 1; l >= 0; l--)
	{
		C.Push(Result / pow(10, l));
		Result = Result % (int)pow(10, l);
	}
}

int main()
{
	List A, B, Result;
	int a;

	ifstream input_file;
	input_file.open("List_Input_A.txt");
	while (!input_file.eof())
	{
		input_file >> a;
		A.Push(a);
	}
	input_file.close();

	input_file.open("List_Input_B.txt");
	while (!input_file.eof())
	{
		input_file >> a;
		B.Push(a);
	}
	input_file.close();

	// Sum1(A, B, Result);
	Sum2(A, B, Result);
	Result.Print();
	
	A.Cear();
	B.Cear();
	Result.Cear();
	return 0;
}