#include <iostream>
#include <vector>
#include <queue>
#include "queue_priority_double.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <ctime>

using namespace std;

struct Pair
{
	int to;
	float weight;
};

class graph
{
private:
	vector<bool> used;
	vector<vector<Pair> > G;

	vector<float > distance;
public:
	int GetSize();
	void clear();
	void print();

	void Deixtry(int);

	void read_from_file(string);
	void generate_graph(int);
	void refresh();
	// ~graph();
};
void graph::clear()
{
	G.clear();
	distance.clear();
}
void graph::refresh()
{
	for (int i = 0; i < distance.size(); ++i)
	{
		distance[i] = 1000000;
	}
}
void graph::Deixtry(int start)
{
	int current;
	float curDis;
	queue_priority<int , float> q;
	distance[start] = 0;
	for (int i = 0; i < distance.size(); i++)
		q.push(i, distance[i]);

	while (!q.isEmpty())
	{
		// cout << q.size() << endl;
		q.del_back(current, curDis);
		for (int n = 0; n < G[current].size(); n++)
		{
			if (distance[G[current][n].to] > distance[current] + G[current][n].weight)
			{
				distance[G[current][n].to] = distance[current] + G[current][n].weight;
				q.erase(G[current][n].to);
				q.push(G[current][n].to, distance[G[current][n].to]);
			}
		}
	}
	// for (int a = 0; a < distance.size(); a++)
	// {
	// 	cout << distance[a] << " ";
	// }
	// cout << endl;
}
void graph::print()
{
	for (int i = 0; i < G.size(); i++)
	{
		cout << i << " -> ";
		for (int j = 0; j < G[i].size(); j++)
		{
			cout << "(" << G[i][j].to << ", " << G[i][j].weight << ") ";
		}
		cout << endl;
	}
}
void graph::read_from_file(string file_name)
{
	// build graph from file
	int size, from;
	Pair tmp;
	// Edge TMP;

	ifstream file(file_name);
	file >> size;
	G.resize(size);
	used.resize(size);
	distance.resize(size);
	for (int i = 0; i < size; ++i)
	{
		used[i] = false;
		distance[i] = 1000000;
	}

	file >> from;
	while (!file.eof())
	{
		file >> tmp.to >> tmp.weight;

		G[from].push_back(tmp);
		swap(tmp.to, from);
		G[from].push_back(tmp);

		file >> from;
	}
	file.close();
	print();
}
void graph::generate_graph(int V)
{
	bool **d;
	Pair tmp;
	G.resize(V);
	used.resize(V);
	distance.resize(V);
	int locNeighbor, locWeight, delta;
	int *countNeighbor = new int[V];
	d = new bool*[V];
	for (int i = 0; i < V; ++i)
	{
		used[i] = false;
		countNeighbor[i] = 0;

		d[i] = new bool[V];
		for (int j = 0; j < V; ++j)
			d[i][j] = false;
	}
	cout << "additional matrix created..." << endl;
	for (int v = 0; v < V; ++v)
	{
		delta = V / 4 - countNeighbor[v];
		for (int n = 0; n < delta; ++n)
		{
			tmp.to = rand() % V;
			while (d[v][tmp.to])
				tmp.to = rand() % V;
			tmp.weight = rand() % 1000 + 1;
			G[v].push_back(tmp);
			d[v][tmp.to] = true;
			countNeighbor[v]++;

			locNeighbor = tmp.to;
			tmp.to = v;
			G[locNeighbor].push_back(tmp);
			d[locNeighbor][tmp.to] = true;
			countNeighbor[locNeighbor]++;
		}
	}
	for (int z = 0; z < V; z++)
	{
		delete [] d[z];
	}
	delete [] countNeighbor;
	cout << "generation graph completed success..." << endl;
}
int main()
{
	srand(time(NULL));
	clock_t start;
	double duration;

	graph R;
	// R.read_from_file("dybil_graph.txt");
	int V = 1000;
	for (int j = 17000; j < 21000; j += 1000)
	{
		cout << j << endl;
		R.generate_graph(j);
		R.refresh();
		for (int i = 0; i < 5; ++i)
		{
			start = clock();
			R.Deixtry(rand() % V);
			duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			cout << duration << endl;
			R.refresh();
		}
		R.clear();
	}
}