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
	int *Visited;
	int Size;
	bool loop;
public:
	Graph();
	void PrintGraph();
	void TopologicalSort();
	bool TopologicalDFS(int);
	~Graph();
};

int main()
{
	Graph A;
	A.PrintGraph();
	A.TopologicalSort();
	A.PrintGraph();
	A.~Graph();
	return 0;
}

Graph::Graph(void)
{
	int s, e;

	ifstream Input;
	//Input.open("TopologicalSort.txt");
	Input.open("topologicalsort.txt");
    if (!Input.is_open())
	{
		cout << "Error: Can't find file." << endl;
		return;
	}
	Input >> Size;
	G = new list<int>[Size];
	Visited = new int[Size];

	Input >> s;
	while (!Input.eof())
	{
		Input >> e;
		G[--s].push_back(--e);
		Input >> s;
	}

	Input.close();
	for (int i = 0; i < Size; i++)
		Visited[i] = 0;
	loop = false;
}
Graph::~Graph(void)
{
	delete [] Visited;
	delete [] G;
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
	if (loop) return; 					// якщо ми виявили цикл, то не виводимо нашого стеку
	for (int j = 0; j < TopologicalStack.size() + j; j++)
	{
		cout << TopologicalStack.top() + 1 << " ";
		TopologicalStack.pop();
	}
	cout << endl;
}

void Graph::TopologicalSort()
{
	bool b;
	bool *In_point = new bool[Size];
	*In_point = {false};
	int i = 0;
	list<int>::iterator v;

	while (i < Size) 					// перебираємо граф щоб знайти вершини в які нічого не вхадить
	{
		v = G[i].begin();
		for (; v != G[i].end(); *v++)
			In_point[*v] = true;
		i++;
	}
	i = 0;
	for (; i < Size; i++) 				// у вершини із false нічого не входить
	{
		if (!In_point[i])
			b = TopologicalDFS(i);
		if (b)
			break;
	}
	loop = b;
	delete In_point;
}

bool Graph::TopologicalDFS(int vertex)
{
	list<int>::iterator v = G[vertex].begin();
	bool b;
	if (Visited[vertex] == 2) 			// якщо ми були в цій вершині, то вертаємося назад
		return false;
	if (Visited[vertex] == 1)			// якщо ця вершина ВЖЕ в стадії обробки, то це цикл
	{
		cout << "This graph have a loop." << endl;
		return true;					// повертаємо true коли є цикл
	}
	Visited[vertex] = 1;				// позначаємо, що ця вершина в стадії обробки
	for (; v != G[vertex].end(); *v++)
	{
		b = TopologicalDFS(*v);
		if (b)
			return true;
	}
	TopologicalStack.push(vertex);
	Visited[vertex] = 2;				// позначаємо як оброблену
	return false;
}