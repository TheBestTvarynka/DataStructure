#include <iostream>

using namespace std;

struct Element_of_the_Queue
{
	int Value;
	Element_of_the_Queue *Next;
};

class Queue
{
	Element_of_the_Queue *Main;
	Element_of_the_Queue *Position;
public:
	Queue()
	{
		Main = new (Element_of_the_Queue);
		Position=Main;
	};
	void Print()
	{
		Element_of_the_Queue *t;
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
		Element_of_the_Queue *t;
		t=Position;
		t->Next=new Element_of_the_Queue;
		t=t->Next;
		t->Value=Value;
		t->Next=NULL;
		Position=t;
	}
	void Pop()
	{
		Element_of_the_Queue *t;
		Element_of_the_Queue *p;
		t=Main->Next;
		p=t->Next;
		cout<<t->Value<<endl;
		delete t;
		
		Main->Next=p;
	}
	void Front()
	{
		Element_of_the_Queue *t;
		t=Main;
		t=t->Next;
		cout<<t->Value<<endl;
	}
	void Back()
	{
		Element_of_the_Queue *t;
		cout<<Position->Value<<endl;
	}
	int Size()
	{
		int size=0;
		Element_of_the_Queue *t;
		
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











