#include <iostream>
#include <vector>
#include <fstream>						// for file
#include <iomanip>						// for setw(...) function
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
	// our graph is array of "lists" (in this case I use vactor as list)
	vector<vector<Pair> > G;

	// matrix of distances from each vertex to each
	vector<vector<float> > distance;
	vector<vector<int> > path;
public:
	// graph();
	void insert(int, Pair);					// add one edge to graph
	void print();
	void print_matrix();					// print matrix of distances

	void floyd_warshall();

	void read_from_file(string);
	void convert_to_matrix();
	~graph();
};
graph::~graph()
{
	cout << "deconstructor called...";
	G.clear();
}
void graph::insert(int from, Pair item)
{
	// add edge in graph
	if (from >= G.size())
	{
		G.resize(from + 1);
	}
	G[from].push_back(item);
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
void graph::floyd_warshall()
{
	// floyd-warshall algorithm
	for (int k = 0; k < distance.size(); k++)
	{
		for (int j = 0; j < distance.size(); j++)
		{
			if (path[j][k] != 0)
			{
				for (int i = 0; i < distance.size(); i++)
				{
					if (i != j && distance[j][i] > distance[k][i] + distance[j][k])
					{
						distance[j][i] = distance[k][i] + distance[j][k];
						path[j][i] = path[j][k];
					}
				}
			}
		}
	}
	print_matrix();
}
void graph::read_from_file(string file_name)
{
	// read fata graph from file
	int size, from;
	Pair tmp;

	ifstream file(file_name);
	file >> size;
	G.resize(size);

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
void graph::convert_to_matrix()
{
	// in start we have array of lists
	// we convert they in matrix of distances and matrix of paths
	distance.resize(G.size());
	path.resize(G.size());
	for (int i = 0; i < G.size(); i++)
	{
		distance[i].resize(G.size());
		path[i].resize(G.size());
		for (int l = 0; l < G.size(); l++)
		{
			distance[i][l] = 1000000;
			path[i][l] = 0;
		}
	}
	for(int j = 0; j < G.size(); j++)
	{
		distance[j][j] = 0;
		path[j][j] = j;
		for(int k = 0; k < G[j].size(); k++)
		{
			distance[j][G[j][k].to] = G[j][k].weight;
			path[j][G[j][k].to] = G[j][k].to;
		}
	}
}

int main()
{
	graph R;
	R.read_from_file("dybil_graph.txt");
	R.convert_to_matrix();
	cout << "\n minimal lenght of path from each vertex to each: " << endl;
	R.floyd_warshall();
	return 0;
}