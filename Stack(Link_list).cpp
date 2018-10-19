#include <iostream>

using namespace std;

struct Element_of_the_Stack
{
	int Value;
	Element_of_the_Stack *Next;
};

class Stack
{
	Element_of_the_Stack *Main;
	Element_of_the_Stack *Position;
public:
	Stack()
	{
		Main = new (Element_of_the_Stack);
		Main->Next=NULL;
		Position=Main;
	};
	void Print()
	{
		Element_of_the_Stack *t;
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
		Element_of_the_Stack *t;
		t=new (Element_of_the_Stack);
		t->Value=Value;
		t->Next=Main->Next;
		Main->Next=t;
	}
	void Pop()
	{
		Element_of_the_Stack *t;
		Element_of_the_Stack *p;
		t=Main->Next;
		p=t->Next;
		cout<<t->Value<<endl;
		delete t;
		
		Main->Next=p;
	}
	int Size()
	{
		int size=0;
		Element_of_the_Stack *t;
		
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