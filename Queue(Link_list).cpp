#include <iostream>

using namespace std;

struct Node
{
	int Value;
	Node *Next;
};

class Queue
{
	Node *Main;
	Node *Position;
public:
	Queue()
	{
		Main = new (Node);
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
		t=Position;
		t->Next=new Node;
		t=t->Next;
		t->Value=Value;
		t->Next=NULL;
		Position=t;
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
	void Front()
	{
		Node *t;
		t=Main;
		t=t->Next;
		cout<<t->Value<<endl;
	}
	void Back()
	{
		Node *t;
		cout<<Position->Value<<endl;
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
	//~Queue();
};

int main()
{
	Queue A;
	A.Push(5);
	A.Push(9);
	A.Push(1);
	A.Push(7);
	A.Print();
	
	A.Pop();
	A.Pop();
	A.Print();
	system("pause");
	A.Push(6);
	A.Push(12);
	A.Print();
	system("pause");
	A.Pop();
	A.Print();
	system("pause");
	A.Front();
	A.Back();
	cout<<A.Size()<<endl;
	system("pause");
	return 0;
}











