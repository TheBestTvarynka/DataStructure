#include <iostream>

using namespace std;

struct Node
{
	int Value;
	Node *Next;
};

class Stack
{
	Node *Main;
	Node *Position;
public:
	Stack()
	{
		Main = new (Node);
		Main->Next=NULL;
		Position=Main;
	};
	void Print()
	{
		Node *t;
		t=Main;
		t=t->Next;
		while(t!=NULL)
		{
			cout<<t->Value<<" ";
			t=t->Next;
		}
		cout<<endl;
	}
	void Push(int Value)
	{
		Node *t;
		t=new (Node);
		t->Value=Value;
		t->Next=Main->Next;
		Main->Next=t;
	}
	void Pop()
	{
		Node *t;
		Node *p;
		t=Main->Next;
		p=t->Next;
		cout<<t->Value<<endl;
		delete t;
		
		Main->Next=p;
	}
	int Size()
	{
		int size=0;
		Node *t;
		
		t=Main;
		while(t->Next!=NULL)
		{
			t=t->Next;
			size++;
		}
		return size;
	}
	//~Stack();
};

int main()
{
	Stack A;
	
	A.Push(5);
	A.Push(9);
	A.Push(1);
	A.Push(7);
	A.Print();
	cout<<A.Size()<<endl;

	A.Pop();
	A.Pop();
	A.Print();
	cout<<A.Size()<<endl;
	
	return 0;
}