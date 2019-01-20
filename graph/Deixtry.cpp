#include <iostream>
#include <list>
#include <iterator>
#include <fstream>		// it's for using file
#include <limits>		// it's for using infinity(max value of distance)

using namespace std;

struct Node
{
	int Vertex;
	int Weight;
};

class Graph
{
private:
	list<Node> *Vertex;
	bool *Visited;
	int Size;
	ifstream Input;
	int *Distances;
public:
	Graph();
	void PrintGraph();
	int Deixtry(int);
	void InitDeixtry(int );
	//~Graph();
};

int main()
{
	int a;
	Graph A;

	cin >> a;

	A.PrintGraph();
	A.InitDeixtry(a);
	A.PrintGraph();
	return 0;
}

Graph::Graph(void)
{
	int start, end, weight, a;
	list<Node>::iterator v;

	Node Element;

	Input.open("List_Input_A (copy)1.txt");
	if (!Input.is_open())
	{
		cout << "Error: Can't find file." << endl;
		return;
	}

	Input >> Size;
	Visited = new bool[Size];
	Vertex = new list<Node>[Size];
	Distances = new int[Size];
	for (int i = 0; i < Size; i++)
	{
		Distances[i] = numeric_limits<int>::max();
		Visited[i] = false;
	}

	Input >> start;
	while (!Input.eof())
	{
		Input >> end;
		Input >> weight;

		Element.Vertex = --end;
		Element.Weight = weight;

		v = Vertex[--start].end();
		Vertex[start].insert(v, Element);
		Visited[start] = false;

		Input >> start;
	}

	Input.close();
}
void Graph::InitDeixtry(int Point)
{

	Distances[Point] = 0;
	int Next = Point, count = 0;

	while (Next != -1)
		Next = Deixtry(Next);

	// дивимося чи є ще вершини в які ми не заходили
	for (count = 0; count < Size; count++)
	{
		if (Visited[count] == false)
		{
			Next = Deixtry(count);
			while (Next != -1)
				Next = Deixtry(Next);
		}
	}
	cout << endl;
}
int Graph::Deixtry(int Point)
{
	cout << Point + 1 << " ";
	bool b = false;
	list<Node>::iterator i; // перебирає усіх сусідів вершини
	list<Node>::iterator Min = Vertex[Point].begin(); // мінімальний вказує на першого сусіда Point

	while (Min != Vertex[Point].end() && Visited[(*Min).Vertex])
		*Min++;

	for (i = Vertex[Point].begin(); i != Vertex[Point].end(); *i++)
	{
		if (Distances[Point] + (*i).Weight < Distances[(*i).Vertex])
			Distances[(*i).Vertex] = Distances[Point] + (*i).Weight;
		if (Visited[(*i).Vertex] == false && (*Min).Weight >= (*i).Weight)
			Min = i;
	}
	Visited[Point] = true;

	if (Min != Vertex[Point].end()) return (*Min).Vertex;
	else return -1;
}

void Graph::PrintGraph()
{
	list<Node>::iterator v;
	for (int i = 0; i < Size; i++)
	{
		cout << i + 1 << " -> ";
		v = Vertex[i].begin();
		for (; v != Vertex[i].end(); *v++)
			cout << "(" << (*v).Vertex + 1 << ", " << (*v).Weight << ") ";
		cout << endl;
	}

	for (int j = 0; j < Size; j++)
		cout << Distances[j] << " ";
	cout << endl;
}