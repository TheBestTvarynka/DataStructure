#include <iostream>

using namespace std;


class Stack
{
	int *ArrayStack;
	int size;
	int top;
public:
	Stack(const int Size)
	{
		ArrayStack=new int[Size];
		top=0;
		size=Size;
	}
	//~Stack();

	Push(int Value)
	{
		if (top>=size) Increase_array();

		ArrayStack[top]=Value;
		top++;
	}
	Pop()
	{
		if ((top-1)<0) cout<<"Error! Stack is emty!"<<endl;
		if (top<=(size/2))
		{
			Reduce_array();
		}
		top--;
		cout<<"Delete element: "<<ArrayStack[top]<<endl;
	}
	Print()
	{
		for (int i = 0; i < top; i++) cout<<ArrayStack[i]<<" ";
		cout<<endl<<"Size of Stack: "<<size<<endl;
	}
	void Increase_array()
	{
		int newSize=(int)(size*1.5);
		int *NewStack=new int [newSize];
		if (NewStack==NULL)
		{
			cout<<"Cannot increase array."<<endl;
			return;
		}
		for (int i = 0; i < top; i++)
		{
			NewStack[i]=ArrayStack[i];
		}
		delete ArrayStack;
		size=newSize;
		ArrayStack=NewStack;
	}
	void Reduce_array()
	{
		int newSize=(int)(size/2);
		int *NewStack=new int [newSize];
		for (int i = 0; i < top; i++)
		{
			NewStack[i]=ArrayStack[i];
		}
		delete ArrayStack;
		size=newSize;
		ArrayStack=NewStack;
	}
};

int main()
{
	Stack A(5);
	int a=1;

	while(a!=0)
	{
		cin>>a;
		A.Push(a);
	}

	cout<<"Resut: \n";
	A.Print();
	system("pause");
	cout<<"Pop:\n";

	a=1;
	while(a!=0)
	{
		A.Pop();
		cin>>a;
	}

	cout<<"Result: \n";
	A.Print();
	return 0;
}