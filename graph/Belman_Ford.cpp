#include <iostream>
#include <vector>
#include <fstream>
#include <limits>		// it's for using infinity(max value of distance)

using namespace std;

struct edges
{
	int u, v, w;
};

class Graph
{
	vector<edges > Edges;
	ifstream Input;
	int *Distance;
	int Size;
public:
	Graph();
	void PrintGraph();
	void BelmanFord(int);
	//~Graph();

};

int main()
{
	int a;
	Graph A;
	cout << "Enter vertex: ";
	cin >> a;
	A.PrintGraph();
	A.BelmanFord(a);
	A.PrintGraph();
	return 0;
}

void Graph::BelmanFord(int Point)
{
	int vsize = Edges.size();

	Distance[Point] = 0;
	for (int count = 0; count < Size - 1; count++)
	{
		for (int i = 0; i < vsize; i++)
		{
			if (Distance[Edges[i].u] != numeric_limits<int>::max() && Distance[Edges[i].u] + Edges[i].w < Distance[Edges[i].v])
			{
				Distance[Edges[i].v] = Distance[Edges[i].u] + Edges[i].w;
			}
		}
	}
}

Graph::Graph(void)
{
	int e, w, a;
	edges Buff;

	Input.open("List_Input_A (copy).txt");
	if (!Input.is_open())
	{
		cout << "Error: Can't find file." << endl;
		return;
	}
	Input >> Size;
	Distance = new int[Size];

	Input >> a;
	while (!Input.eof())
	{
		Input >> e >> w;
		Buff.u = --a;
		Buff.v = --e;
		Buff.w = w;
		Edges.push_back(Buff);
		Input >> a;
	}
	Input.close();
	for (int i = 0; i < Size; ++i)
		Distance[i] = numeric_limits<int>::max();
}
void Graph::PrintGraph()
{
	for (int i = 0; i < Edges.size(); i++)
	{
		cout << "(" << Edges[i].u + 1 << " " << Edges[i].v + 1 << ") - " << Edges[i].w << endl;
	}

	for (int j = 0; j < Size; j++)
        cout << Distance[j] << " ";
	cout << endl;
}
