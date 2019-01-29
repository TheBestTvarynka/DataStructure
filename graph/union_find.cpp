#include <iostream>

using namespace std;

class union_find
{
	int Size;
	int *Parent;
	int *rank;
public:
	void Init(int );
	~union_find();
	bool union_set(int , int );
	int find_set(int );
	void Print();
};

void union_find::Print()
{
	cout << "-------------------------" << endl;
	for (int i = 0; i < Size; i++)
	{
		cout << i + 1 << " -> " << Parent[i] << endl;
	}
	cout << "-------------------------" << endl;
}
int union_find::find_set(int v)
{
	if (Parent[v] == v)
		return v;
	return Parent[v] = find_set(Parent[v]);
}
bool union_find::union_set(int v, int u)
{
	v = find_set(v);
	u = find_set(u);
	if (u != v)
	{
		if (rank[u] > rank[v])
			swap(u, v);
		Parent[u] = v;
		if (rank[u] == rank[v])
			rank[u]++;
		return true;
	}
	return false;
}
void union_find::Init(int size)			// constructor of the class
{
	Size = size;
	Parent = new int[Size];
	rank = new int[Size];
	for (int i = 0; i < Size; ++i)
	{
		Parent[i] = i;
		rank[i] = 0;
	}
}
union_find::~union_find(void)				// destructor of the class
{
	delete [] Parent;
	delete [] rank;
}