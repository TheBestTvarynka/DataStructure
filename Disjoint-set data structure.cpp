#include <iostream>

using namespace std;

class StDt
{
	int *Parent;
	int *size;
public:
	StDt(const int Size)
	{
		Parent=new int[Size];
		size=new int[Size];
		for (int i = 0; i < Size; ++i)
		{
			Parent[i]=i;
			size[i]=1;
		}
	}
	void BuildStdt()
	{
		int start, end, p;
		p=1;
		
		while(p!=0)
		{
			cout<<"From: ";
			cin>>start;
			cout<<"To: ";
			cin>>end;
			Parent[start-1]=end-1;
			if (size[start-1]>=size[end-1])
			{
				size[end-1]=1+size[start-1];
			}
			cin>>p;
		}
	}
	int Find(int Vertex)
	{
		int p;
		p=Vertex-1;
		while(p!=Parent[p])
		{
			Parent[p]=Parent[Parent[p]];
			cout<<"------ "<<p<<"---"<<Parent[p]<<"---"<<Parent[Parent[p]]<<endl;
			p=Parent[p];
			//Parent[Vertex-1]=p;
		}
		Parent[Vertex-1]=p;
		return p;
	}
	void Connected(int i, int j)
	{
		if (Find(i)==Find(j)) cout<<"This elements connected."<<endl;
		else cout<<"This elements did not connected."<<endl;
	}
	void Join(int i, int j)
	{
		int id_i=Find(i);
		int id_j=Find(j);

		if (size[id_i]<size[id_j]) Parent[id_i]=id_j;
		else Parent[id_j]=id_i;
	}
	//~StDt();
	void Print(int Size)
	{
		for (int i = 0; i < Size; i++)
		{
			cout<<Parent[i]<<" ";
		}
		cout<<endl;
	}
};

int main()
{
	int count;
	int Vertex;
	int a, b;
	
	cout<<"Enter count of point: ";
	cin>>count;

	StDt A(count);
	A.BuildStdt();
	A.Print(count);
	while(true)
	{
		cin>>a;
		cout<<"R "<<A.Find(a)<<endl;
		A.Print(count);
	}
	
	cin>>a>>b;
	A.Connected(a, b);

	A.Join(a, b);
	A.Print(count);
	return 0;
}
