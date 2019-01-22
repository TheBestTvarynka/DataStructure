// вважаємо що граф НЕ ОРІЄГТОВАНИЙ. у протилежному випадку, міняється не багато
// вершина, в яку нічого не входить має бути коренем дерева
// така вершина має бути одна

#include <iostream>
#include <list>
#include <iterator>
#include <fstream>		// it's for using file
#include <vector>

using namespace std;

struct Node
{
	int to;
	int weight;
};

class Graph
{
private:
	list<Node> *graph;
	int Size;
	//vector<Node > graph;
	/////////////////
	vector<int> queue;
public:
	Graph();					// constructor build the graph form file
	void PrintGraph();			// show graph on the screen
	void MST_Prim();			// MST - minimal spanning tree
	//~Graph();
};

int main()
{
	Graph A;
	A.PrintGraph();
	return 0;
}

void Graph::MST_Prim()
{
	// починаємо будувати дерево із першої попавшої вершини
	// по-ідеї нам все одно із якої починати
	queue.push_back(0);
}

Graph::Graph(void)
{
	ifstream Input;
	int start, end, weight;
	list<Node>::iterator v;
	Node Buff;

	Input.open("List_Input_A (copy)1.txt");
	if (!Input.is_open())
	{
		cout << "Error: Can't find file." << endl;
		return;
	}
	Input >> Size;
	graph = new list<Node >[Size];

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
}
void Graph::PrintGraph()
{
	list<Node>::iterator v;
	for (int i = 0; i < Size; i++)
	{
		cout << i + 1 << " -> ";
		v = graph[i].begin();
		for (; v != graph[i].end(); *v++)
			cout << "(" << (*v).to + 1 << ", " << (*v).weight << ") ";
		cout << endl;
	}
}
