#include <iostream>

using namespace std;

class union_find
{
	int Size;
	int *Parent;
	int *rank;
public:
	union_find(int );
	~union_find();
	void union_set(int , int );
	int find_set(int );
};

int union_find::find_set(int v)
{
	if (Parent[v] == v)
		return v;
	return Parent[v] = find_set(Parent[v]);
}
void union_find::union_set(int v, int u)
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
	}
}
union_find::union_find(int size)
{
	Size = size;
	Parent = new int[Size];
	rank = new int[Size];
	for (int i = 0; i < Size; ++i)
	{
		Parent[i] = i + 1;
		rank[i] = 0;
	}
}
union_find::~union_find(void)
{
	delete [] Parent;
}