#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pair
{
	int to, weight;
};

class graph
{
private:
	vector<vector<int> > eheuristic_table;
	vector<vector<int> > G;
	vector<string> cities;

	vector<int> path;
	int lenght;
	vector<bool> used;
public:
	graph();
	void greedy_search(int, int);
	void a_Star(int, int);
	void show_cities();

	int GetId(string);
	void refresh();
	~graph();
	bool in_path(int);
};
graph::graph()
{
	G.resize(15);
	used.resize(15);
	eheuristic_table.resize(15);
	cities.resize(15);
	for (int i = 0; i < 15; ++i)
	{
		G[i].resize(15);
		eheuristic_table.resize(15);
		used[i] = false;
	}
	G = {
		{0, 0, 0, 171, 139, 220, 110, 0, 0, 0, 0, 0, 0, 0, 215},
		{0, 0, 0, 0, 337, 0, 0, 0, 0, 350, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 250, 0, 0, 0, 0, 0, 0, 0, 116, 167, 0},
		{171, 0, 0, 0, 0, 0, 117, 0, 0, 0, 0, 0, 0, 177, 0},
		{139, 337, 250, 0, 0, 0, 0, 0, 0, 0, 223, 0, 0, 0, 0},
		{220, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
		{110, 0, 0, 117, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 175, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 336, 0, 0, 0},
		{0, 350, 0, 0, 0, 0, 0, 0, 0, 0, 257, 0, 0, 0, 0},
		{0, 0, 0, 0, 223, 0, 0, 0, 0, 257, 0, 130, 0, 217, 0},
		{0, 0, 0, 0, 0, 0, 0, 175, 336, 0, 130, 0, 0, 0, 0},
		{0, 0, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 167, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{215, 0, 0, 0, 0, 0, 0, 0, 0, 0, 217, 0, 0, 0, 0}
	};
	eheuristic_table = {
		{0, 295, 250, 144, 119, 205, 108, 294, 280, 415, 230, 284, 158, 254, 190},
		{295, 0, 430, 403, 241, 289, 337, 324, 112, 227, 88 , 205, 367, 479, 114},
		{250, 430, 0, 225, 191, 400, 161, 233, 71 , 527, 373, 335, 99 , 136, 413},
		{144, 403, 225, 0, 216, 212, 107, 378, 260, 595, 363, 421, 130, 143, 318},
		{119, 241, 191, 216, 0, 304, 120, 177, 178, 377, 176, 190, 133, 256, 229},
		{205, 289, 400, 212, 304, 0, 248, 485, 466, 547, 346, 435, 294, 343, 198},
		{108, 337, 161, 107, 120, 248, 0, 277, 198, 509, 287, 306, 60 , 158, 268},
		{294, 324, 233, 378, 177, 485, 277, 0, 120, 287, 245, 131, 241, 346, 372},
		{280, 112, 71 , 260, 178, 466, 198, 120, 0, 381, 355, 267, 175, 243, 440},
		{415, 227, 527, 595, 377, 547, 509, 287, 381, 0, 209, 156, 490, 638, 375},
		{230, 88 , 373, 363, 176, 346, 287, 245, 355, 209, 0, 110, 306, 428, 180},
		{284, 205, 335, 421, 190, 435, 306, 131, 267, 156, 110, 0, 302, 433, 283},
		{158, 367, 99 , 130, 133, 294, 60 , 241, 175, 490, 306, 302, 0, 145, 325},
		{254, 479, 136, 143, 256, 343, 158, 346, 243, 638, 428, 433, 145, 0, 418},
		{190, 114, 413, 318, 229, 198, 268, 372, 440, 375, 180, 283, 325, 418, 0}
	};
	cities = {
		"Warshawa",
		"Gdansk",
		"Krakow",
		"Lublin",
		"Lodz",
		"Belostok",
		"Radom",
		"Wroclaw",
		"Katowice",
		"Schecin",
		"Bydgoch",
		"Poznan",
		"Kelce",
		"Geshuv",
		"Olshtin"
	};
}
graph::~graph()
{
	G.clear();
	eheuristic_table.clear();
}
bool graph::in_path(int c)
{
	return used[c];
}
int graph::GetId(string city)
{
	int i = 0;
	while (cities[i] != city)
		i++;
	return i;
}
void graph::refresh()
{
	for (int i = 0; i < 15; ++i)
		used[i] = false;
}
void graph::greedy_search(int from, int to)
{
	path.clear();
	refresh();
	lenght = 0;
	int current = from, min_h, next, a;

	// add first point to path and mark them as used
	path.push_back(from);
	used[from] = true;
	while (current != to)
	{
		next = 0;
		// search frist point that will ne available
		while ((G[current][next] == 0 || in_path(next)) && next < 15)
			next++;
		// this statement execute when we are deadlocked
		if (next >= 15)
		{
			a = path.size();
			lenght -= G[path[a - 1]][path[a - 2]];
			path.pop_back();
			current = path[path.size() - 1];
			continue;
		}
		min_h = eheuristic_table[next][to];
		// pass throught the loop and search minimal eheuristic value (min_h)
		for (int i = 0; i < 15; i++)
		{
			if (G[current][i] != 0 && !in_path(i) && eheuristic_table[i][to] < min_h)
			{
				min_h = eheuristic_table[i][to];
				next = i;
			}
		}
		// we find min_h
		lenght += G[current][next];
		// add finded point to path and mark as used
		path.push_back(next);
		used[next] = true;
		current = next;
	}
	// print_vector(path);
	cout << cities[path[0]];
	for (int j = 1; j < path.size(); j++)
		cout << " -> " << cities[path[j]];
	cout << endl << "lenght: " << lenght << endl;
}
void graph::show_cities()
{
	for (int i = 0; i < cities.size(); ++i)
		cout << i << " - " << cities[i] << endl;
}
void graph::a_Star(int from, int to)
{
	refresh();
	lenght = 0;
	path.clear();
	int current = from, min_h, next, a;

	path.push_back(from);
	used[from] = true;
	while (current != to)
	{
		next = 0;
		while ((G[current][next] == 0 || in_path(next)) && next < 15)
			next++;
		if (next >= 15)
		{
			a = path.size();
			lenght -= G[path[a - 1]][path[a - 2]];
			path.pop_back();
			current = path[path.size() - 1];
			continue;
		}
		min_h = lenght + G[current][next] + eheuristic_table[next][to];
		for (int i = next + 1; i < 15; i++)
		{
			if (G[current][i] != 0 && !in_path(i) && lenght + G[current][i] + eheuristic_table[i][to] < min_h)
			{
				min_h = eheuristic_table[i][to] + lenght + G[current][i];
				next = i;
			}
		}
		lenght += G[current][next];
		path.push_back(next);
		used[next] = true;
		current = next;
	}
	// print_vector(path);
	cout << cities[path[0]];
	for (int j = 1; j < path.size(); j++)
		cout << " -> " << cities[path[j]];
	cout << endl << "lenght: " << lenght << endl;
}

int main()
{
	cout << "Laba.4.Eheuristic algorithms" << endl;
	graph R;
	int from, to;
	R.show_cities();
	for (int i = 0; i < 5; ++i)
	{
		cin >> from >> to;
		R.greedy_search(from, to);
		R.refresh();
		R.a_Star(from, to);
		R.refresh();
	}
	return 0;
}