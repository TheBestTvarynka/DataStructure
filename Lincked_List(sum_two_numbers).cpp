#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

struct Element_of_the_List
{
	int Value;
	Element_of_the_List *Next;
};

class List
{
	Element_of_the_List *Main;
	Element_of_the_List *Position;
public:
	List()
	{
		Main = new (Element_of_the_List);
		Position=Main;
	};
	void Print()
	{
		Element_of_the_List *t;
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
		Element_of_the_List *t;
		t=Position;
		t->Next=new Element_of_the_List;
		t=t->Next;
		t->Value=Value;
		t->Next=NULL;
		Position=t;
	}
	int Pop()
	{
		int e;
		Element_of_the_List *t;
		Element_of_the_List *p;

		t=Main->Next;
		if (t==NULL)
		{
			return 0;
		}
		p=t->Next;
		//cout<<t->Value<<endl;
		e=t->Value;
		delete t;
		
		Main->Next=p;
		return e;
	}
	int is_emty()
	{
		Element_of_the_List *t;
		t=Main->Next;
		if (t==NULL) return 0;
		else return 1;
	}
	int Front()
	{
		Element_of_the_List *t;
		t=Main;
		t=t->Next;
		if(t!=NULL) return t->Value;
		else return 0;
	}
	void Back()
	{
		cout<<Position->Value<<endl;
	}
	int Size()
	{
		int size=0;
		Element_of_the_List *t;
		
		t=Main;
		while(t->Next!=NULL)
		{
			t=t->Next;
			size++;
		}
		return size;
	}
	//~List();
};

// void Sum(List &A, List &B, List &C)
// {
// 	int sum, rem=0;
// 	while(A.is_emty()!=0 || B.is_emty()!=0)
// 	{
// 		//cout<<A.Front()<<" "<<B.Front()<<endl;
// 		sum=A.Pop() + B.Pop();
// 		C.Push((sum + rem)%10);
// 		rem=(int)((sum + rem)/10);
// 	}
// 	if(rem==1) C.Push(1);
// }

void Sum(List &A, List &B, List &C)
{
	int First=0, Second=0, Result;
	int n, n1;

	n=A.Size();
	for (int i = 1; i <= n; i++) First += A.Pop()*pow(10, (n-i));
	cout<<First<<endl;
	
	n1=B.Size();
	for (int j = 1; j <= n; j++) Second += B.Pop()*pow(10, (n-j));
	cout<<Second<<endl;
	
	Result = First + Second;
	cout<<Result<<endl;
	
	if(n<n1) n=n1;
	if (Result>=pow(10, n)) n++;

	for (int l = n-1; l >= 0; l--)
	{
		C.Push(Result/pow(10, l));
		Result=Result%(int)pow(10, l);
	}
}

int main()
{
	List A, B;
	List Result;
	int a;

	ifstream input_file;
	input_file.open("List_Input_A.txt");
	while(!input_file.eof())
	{
		input_file>>a;
		A.Push(a);
	}
	input_file.close();
	
	input_file.open("List_Input_B.txt");
	while(!input_file.eof())
	{
		input_file>>a;
		B.Push(a);
	}
	input_file.close();
	
	Sum(A, B, Result);
	Result.Print();
	
	system("pause");
	return 0;
}
