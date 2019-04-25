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

class graph
{
private:
	vector<bool> used;
	// our graph is array of "lists" (in this case I use vactor as list)
	vector<vector<Pair> > G;

	// matrix of distances from each vertex to each
	vector<vector<float> > distance;
public:
	// graph();
	void insert(int, Pair);					// add one edge to graph
	void print();
	void print_matrix();					// print matrix of distances
	int GetSize();							// return count of vertex

	void Deixtry(int);

	void refresh(int);						// fill start values
	void alloc();							// alloc memory from used[] and distance[][]
	void read_from_file(string);
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
void graph::Deixtry(int start)
{
	// algorithm Deixtry
	int curent;
	queue_priority<int, float> order_deixtry;

	distance[start][start] = 0;
	used[start] = true;
	order_deixtry.push(start, distance[start][start]);

	while (order_deixtry.pop(curent))
	{
		used[curent] = true;
		for (int i = 0; i < G[curent].size(); i++)
		{
			if (used[G[curent][i].to] == false)
				order_deixtry.push(G[curent][i].to, G[curent][i].weight);
			if (distance[start][curent] + G[curent][i].weight < distance[start][G[curent][i].to])
			{
				// update distance
				distance[start][G[curent][i].to] = distance[start][curent] + G[curent][i].weight;
			}
		}
	}
	// print result
	for (int j = 0; j < G.size(); j++)
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
	cout << "\n minimal lenght of path from each vertex to each: " << endl;
	cout << "===================================================================" << endl;
	for (int d = 0; d < R.GetSize(); d++)
	{
		R.Deixtry(d);
		R.refresh(0);
	}
	cout << "===================================================================" << endl;
	return 0;
}