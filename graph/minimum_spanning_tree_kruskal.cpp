#include <iostream>
#include <vector>
#include <fstream>
#include "union_find.cpp"
using namespace  std;

struct Edge
{ int from, to, weight; };
struct Node
{ int to, weight; };

class Graph
{
	vector<Node > *graph;
	int Size;
	//////////////////////
	vector<Edge > edges;
	union_find plural;
	vector<Node > *mst;				// final minimal spanning tree
public:
	Graph();
	~Graph();
	void MST_Kruskal();				// MST - minimal spanning tree
	void Insert_queue(Edge );
	void Insert_mst(Edge );
	void Print(vector<Node > *);
};

int main()
{
	Graph A;
	A.MST_Kruskal();
	A.~Graph();
	return 0;
}

void Graph::MST_Kruskal()
{
	while (edges.size() != 0)
	{
		if (plural.union_set(edges[0].from, edges[0].to))
			Insert_mst(edges[0]);
		edges.erase(edges.begin());
	}
	Print(mst);
}
void Graph::Insert_mst(Edge e)
{
	Node Buff;
	Buff.to = e.to;
	Buff.weight = e.weight;
	mst[e.from].push_back(Buff);
}
void Graph::Insert_queue(Edge e)
{
	int count = 0, size = edges.size();
	while (count < size && e.weight > edges[count].weight)
		count++;
	edges.insert(edges.begin() + count, e);
}
void Graph::Print(vector<Node > *St)
{
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	for (int i = 0; i < Size; i++)
	{
		cout << i + 1 << " -> ";
		for (int v = 0; v < St[i].size(); v++)
			cout << "(" << St[i][v].to + 1 << ", " << St[i][v].weight << ") ";
		cout << endl;
	}
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}
Graph::Graph(void)
{
	ifstream Input;
	int start;
	Node Buff;
	Edge e;

	Input.open("List_Input_A (copy)1.txt");
	if (!Input.is_open())
	{
		cout << "Error: Can't find file." << endl;
		return;
	}
	Input >> Size;
	graph = new vector<Node >[Size];
	mst = new vector<Node >[Size];
	plural.Init(Size);

	Input >> start;
	while (!Input.eof())
	{
		start--;
		Input >> Buff.to >> Buff.weight;
		Buff.to--;
		graph[start].push_back(Buff);
		e.from = start;
		e.to = Buff.to;
		e.weight = Buff.weight;
		Insert_queue(e);			// add edge in queue
		Input >> start;
	}
	cout << "i wrote data in graph" << endl;
	Input.close();
	Print(graph);
}
Graph::~Graph(void)
{
	delete [] graph;
	//delete [] mst;
	plural.~union_find();
}