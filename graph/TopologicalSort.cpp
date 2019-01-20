#include <iostream>
#include <list>
#include <stack>
#include <iterator>
#include <fstream>

using namespace std;

class Graph
{
private:
	list<int> *G;
	stack<int> TopologicalStack;
	bool *Visited;
	int Size;
public:
	Graph();
	void PrintGraph();
	void TopologicalSort();
	void TopologicalDFS(int);
	//~Graph();
};

int main()
{
	Graph A;
	A.PrintGraph();
	A.TopologicalSort();
	A.PrintGraph();

	return 0;
}

Graph::Graph(void)
{
	int s, e;

	ifstream Input;
	Input.open("TopologicalSort.txt");
    if (!Input.is_open())
	{
		cout << "Error: Can't find file." << endl;
		return;
	}
	Input >> Size;

	G = new list<int>[Size];
	cout << "qwe" << endl;
	Visited = new bool[Size];

	Input >> s;
	while (!Input.eof())
	{
		Input >> e;
		G[--s].push_back(--e);
		Input >> s;
	}

	Input.close();
	for (int i = 0; i < Size; i++)
		Visited[i] = false;
}

void Graph::PrintGraph()
{
	list<int>::iterator v;
	for (int i = 0; i < Size; i++)
	{
		cout << i + 1 << " -> ";
		v = G[i].begin();
		for (; v != G[i].end(); *v++)
			cout << (*v) + 1 << " ";
		cout << endl;
	}
	for (int j = 0; j < TopologicalStack.size() + j; j++)
	{
		cout << TopologicalStack.top() + 1 << " ";
		TopologicalStack.pop();
	}
	cout << endl;
}

void Graph::TopologicalSort()
{
	bool *In_point = new bool[Size];
	*In_point = {false};
	int i = 0;
	list<int>::iterator v;

	while (i < Size) // перебираємо граф щоб знайти вершини в які нічого не вхадить
	{
		v = G[i].begin();
		for (; v != G[i].end(); *v++)
			In_point[*v] = true;
		i++;
	}

	i = 0;
	for (; i < Size; i++) // у вершини із false нічого не входить
	{
		if (!In_point[i])
			TopologicalDFS(i);
	}
	delete In_point;
}

void Graph::TopologicalDFS(int vertex)
{
	list<int>::iterator v = G[vertex].begin();
	for (; v != G[vertex].end(); *v++)
		TopologicalDFS(*v);
	if (!Visited[vertex])
	{
		TopologicalStack.push(vertex);
		Visited[vertex] = true;
	}
}
