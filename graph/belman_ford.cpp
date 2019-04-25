#include <iostream>
#include <vector>
#include <fstream>						// for file
#include <iomanip>						// for setw(...) function
#include "queue_priority_double.h"		// for Deixtry algorithm
#include <string>						// we save path of file in string

using namespace std;

struct Pair
{
	int to;
	float weight;
};
struct Edge
{
	int u, v;
	float w;
};

class graph
{
private:
	vector<bool> used;
	// our graph is array of "lists" (in this case I use vactor as list)
	vector<vector<Pair> > G;

	// matrix of distances from each vertex to each
	vector<vector<float> > distance;
	// for belman-ford (array of edges)
	vector<Edge> Gg;
public:
	// graph();
	void insert(int, Pair);					// add one edge to graph
	void print();
	void print_matrix();					// print matrix of distances
	int GetSize();							// return count of vertex

	void BelmanFord(int);

	void refresh(int);						// fill start values
	void alloc();							// alloc memory from used[] and distance[][]
	void read_from_file(string);
	void convert_to_array();				// convert array of lists to array of edges
	~graph();
};
graph::~graph()
{
	cout << "deconstructor called...";
	G.clear();
	used.clear();
}
int graph::GetSize()
{ return G.size(); }
void graph::insert(int from, Pair item)
{
	// add edge in graph
	if (from >= G.size())
	{
		G.resize(from + 1);
		used.resize(from + 1);
	}
	G[from].push_back(item);
	used[from] = false;
}
void graph::print()
{
	// print graph
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
void graph::print_matrix()
{
	// print matrix of destances
	cout << "===================================================================" << endl;
	for (int i = 0; i < distance.size(); i++)
	{
		for(int j = 0; j < G.size(); j++)
		{
			cout << setw(3) << distance[i][j] << " ";
		}
		cout << endl;
	}
	cout << "===================================================================" << endl;
}
void graph::BelmanFord(int start)
{
	bool flg = false;
	int vsize = Gg.size(), Size = G.size();
	vector<int > v;

	distance[start][start] = 0;
	for (int count = 0; count < Size; count++)
	{
		flg = false;
		for (int i = 0; i < vsize; i++)
		{
			if (distance[start][Gg[i].u] != 1000000)
			{
				if (distance[start][Gg[i].u] + Gg[i].w < distance[start][Gg[i].v])
				{
					distance[start][Gg[i].v] = distance[start][Gg[i].u] + Gg[i].w;
					flg = true;
				}
			}
		}
		if (!flg) break;
	}
	for (int j = 0; j < distance[start].size(); j++)
		cout << setw(3) << distance[start][j] << " ";
	cout << endl;
}
void graph::read_from_file(string file_name)
{
	// read fata graph from file
	int size, from;
	Pair tmp;

	ifstream file(file_name);
	file >> size;
	G.resize(size);
	used.resize(size);

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
void graph::convert_to_array()
{
	Edge tmp;
	for (int i = 0; i < G.size(); i++)
	{
		tmp.u = i;
		for (int j = 0; j < G[i].size(); j++)
		{
			tmp.v = G[i][j].to;
			tmp.w = G[i][j].weight;
			Gg.push_back(tmp);
		}
	}
}
void graph::refresh(int k)
{
	// we fill in used[] array and distances[][] matrix start values
	// k == 0 - refresh only used[]
	// k == 1 - refresh only distances[][]
	// k == 2 - refresh both
	for (int i = 0; i < G.size(); i++)
	{
		if (k == 0 || k == 2)
			used[i] = false;
		if (k == 1 || k == 2)
		{
			for (int j = 0; j < G.size(); j++)
				distance[i][j] = 1000000;
		}
	}
}
void graph::alloc()
{
	// allocate memory for used[] array of distance[][] matrix
	used.resize(G.size());
	distance.resize(G.size());
	for (int i = 0; i < G.size(); i++)
	{
		used[i] = false;
		distance[i].resize(G.size());
		for (int j = 0; j < G.size(); j++)
			distance[i][j] = 1000000;
	}
}

int main()
{
	graph R;
	R.read_from_file("dybil_graph.txt");
	R.alloc();
	R.convert_to_array();
	cout << "\n minimal lenght of path from each vertex to each: " << endl;
	cout << "===================================================================" << endl;
	for (int d = 0; d < R.GetSize(); d++)
	{
		R.BelmanFord(d);
	}
	cout << "===================================================================" << endl;
	return 0;
}