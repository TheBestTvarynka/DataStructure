// вважаємо що граф не орієнтований. задається списками сміжнисті.
// дана реалізація більш оптимальна для розріджених графів.

#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

struct Node
{ int to, weight; };

struct edge
{ int from, to, weight; };

class Graph
{
private:
	vector<Node> *graph;
	int Size;
	/////////////////
	vector<edge> queue;
	vector<Node> *mst;			// final minimal spanning tree
	bool *used;
public:
	Graph();					// constructor build the graph form file
	~Graph();					// destructor free memory
	void MST_Prim();			// MST - minimal spanning tree
	void Insert_queue(edge );
	void Insert_mst(edge );
	void Print(vector<Node > *);
};

int main()
{
	Graph A;
	A.MST_Prim();
	A.~Graph();
	return 0;
}

void Graph::MST_Prim()
{
	// починаємо будувати дерево із першого попавшго ребра
	// по-ідеї нам все одно із якого починати, тому беремо перше ребро із графа
	edge Buff;
	Buff.from = 0;
	Buff.to = graph[0][0].to;
	Buff.weight = graph[0][0].weight;
	queue.insert(queue.begin(), Buff);
	for (int j = 1; j < graph[0].size(); j++)
	{
		Buff.to = graph[0][j].to;
		Buff.weight = graph[0][j].weight;
		Insert_queue(Buff);
	}
	used[0] = true;

	while (queue.size() != 0)
	{
		while (used[queue[0].to] && queue.size() >= 1)
			queue.erase(queue.begin());
		if (queue.size() == 0)
		{
			Print(mst);
			return;
		}

		Insert_mst(queue[0]);			// add minimal edge in mst
		Buff.from = queue[0].to;
		used[queue[0].to] = true;		// mart as used
		queue.erase(queue.begin());		// delete current (first) edge becouse it in tree
		for (int i = 0; i < graph[Buff.from].size(); i++)
		{
			Buff.to = graph[Buff.from][i].to;
			Buff.weight = graph[Buff.from][i].weight;
			Insert_queue(Buff);
		}
	}
}
void Graph::Insert_queue(edge e)
{
	if (used[e.to])
		return;
	int count = 0, size = queue.size();
	while (e.weight > queue[count].weight && count < size)
		count++;
	queue.insert(queue.begin() + count, e);
}
void Graph::Insert_mst(edge e)
{
	Node Buff;
	Buff.to = e.to;
	Buff.weight = e.weight;
	mst[e.from].push_back(Buff);
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
	int start, end, weight;
	Node Buff;

	Input.open("List_Input_A (copy)1.txt");
	if (!Input.is_open())
	{
		cout << "Error: Can't find file." << endl;
		return;
	}
	Input >> Size;
	graph = new vector<Node >[Size];
	mst = new vector<Node >[Size];
	used = new bool[Size];
	for (int i = 0; i < Size; i++)
		used[i] = false;

	Input >> start;
	while (!Input.eof())
	{
		Input >> end >> weight;

		Buff.to = --end;
		Buff.weight = weight;
		graph[--start].push_back(Buff);

		Input >> start;
	}
	Input.close();
	Print(graph);
}
Graph::~Graph(void)
{
	delete [] used;
	delete [] graph;
	// delete [] mst;
}