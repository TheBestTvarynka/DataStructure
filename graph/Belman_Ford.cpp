#include <iostream>
#include <vector>
#include <fstream>
#include <limits>		// it's for using infinity(max value of distance)

using namespace std;

struct edges
{ int u, v, w; };

class Graph
{
	vector<edges > G;
	ifstream Input;
	int *Distance;
	bool *Visited;
	int Size;
public:
	Graph();
	void PrintGraph();
	void BelmanFord(int );
	void DFS(int );
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

void Graph::DFS(int Point)
{
	if (Visited[Point] == true)
		return;

	Distance[Point] = numeric_limits<int>::min();
	Visited[Point] = true;
	for (int i = 0; i < G.size(); i++)
	{
		if (G[i].u == Point && Visited[G[i].v] == false)
			DFS(G[i].v);
	}
}
void Graph::BelmanFord(int Point)
{
	int vsize = G.size(), INF = numeric_limits<int>::max();
	vector<int > v;
	bool flg = false; // він просто поліпшує роботу
	// Якшо на якійсь ітерації ми нічого не змінили
	// то і на наступній нічого нее змінимо

	Distance[Point] = 0;
	for (int count = 0; count < Size; count++)
	{
		flg = false;
		for (int i = 0; i < vsize; i++)
		{
			if (Distance[G[i].u] != INF)
			{
				if (Distance[G[i].u] + G[i].w < Distance[G[i].v])
				{
					if (count == Size - 1)
					{
						// це означає що вершина u лежить на циклі (<0) або на ребрах, що ведуть від циклів
						// від u ми маємо запустити пошук в глибину (dfs)
						v.push_back(G[i].v);
					}
					else Distance[G[i].v] = Distance[G[i].u] + G[i].w;
					flg = true;
				}
			}
		}
		if (!flg) break;
	}
	if (v.size() != 0)
	{
		Visited = new bool[Size];
		for (int t = 0; t < Size; t++) Visited[t] = false;
		for (int j = 0; j < v.size(); j++)
			DFS(v[j]);
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
		G.push_back(Buff);
		Input >> a;
	}
	Input.close();
	for (int i = 0; i < Size; ++i)
		Distance[i] = numeric_limits<int>::max();
}
void Graph::PrintGraph()
{
	for (int i = 0; i < G.size(); i++)
		cout << "(" << G[i].u + 1 << " " << G[i].v + 1 << ") - " << G[i].w << endl;
	cout << "Distances: " << endl;
	for (int j = 0; j < Size; j++)
		cout << Distance[j] << " ";
	cout << endl;
}
