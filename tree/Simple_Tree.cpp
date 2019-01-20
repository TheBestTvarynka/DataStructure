#include <iostream>
#include <fstream>

using namespace std;

struct Branch
{
	int Key;
	bool Height;
	Branch *LeftBranch, *RightBranch;
};

class Tree
{
	int tabs;
public:
	Branch *Main;

	Tree(int Key)
	{
		Main = new (Branch);
		Main->LeftBranch = NULL;
		Main->RightBranch = NULL;
		Main->Key = Key;
		Main->Height = true;
		tabs = 0;
	}
	bool Insert(int, Branch *);
	bool Search_LCA(int, int, Branch *, Branch *&);
	void PrintTree(Branch *);
	void ClearTree(Branch *);
	//~Tree();
};

int main()
{
	Branch *lca = NULL;
	int a, f, s;

	Tree Example(56);

	ifstream input_file;
	input_file.open("List_Input_A.txt");
	while (!input_file.eof())
	{
		input_file >> a;
		Example.Insert(a, Example.Main);
	}
	input_file.close();

	Example.PrintTree(Example.Main);
	cout << "Build tree finished." << endl;

	cin >> f >> s;
	Example.Search_LCA(f, s, Example.Main, lca);

	if (lca != NULL) cout << lca->Key << endl;
	else cout << "LCA not found." << endl;

	Example.ClearTree(Example.Main);
	return 0;
}

bool Tree::Search_LCA(int a, int b, Branch *Node, Branch *(&Find))
{
	if (Node == NULL) return false;
	if (Find != NULL) return true;
	// cout << Node->Key << endl;

	bool left = false, right = false, node = false;
	if (Node->Key == a || Node->Key == b)
		node = true;

	left = Search_LCA(a, b, Node->LeftBranch, Find);
	if(Find == NULL) right = Search_LCA(a, b, Node->RightBranch, Find);

	if (left == true && right == true)
	{
		Find = Node;
		cout << "Find LCA: " << Find->Key <<endl;
		return true;
	}
	if ((left == true || right == true))
	{
		if (node == true)
		{
			Find = Node;
			cout << "Find LCA: " << Find->Key <<endl;
		}
		return true;
	}
	if (node == true) return true;
	else return false;
}

void Tree::PrintTree(Branch *Node)
{
	if (!Node) return;
	tabs++;

	PrintTree(Node->LeftBranch);

	for (int i = 0; i < tabs; i++) cout << "  ";
	cout << Node->Key << endl;

	PrintTree(Node->RightBranch);

	tabs--;
	return;
}

bool Tree::Insert(int Key, Branch *Node)
{
	bool val;
	Branch *t;
	if (Node->LeftBranch == NULL)
	{
		Node->LeftBranch = new (Branch);
		t = Node->LeftBranch;
		t->Key = Key;
		t->Height = true;
		t->RightBranch = NULL;
		t->LeftBranch = NULL;
		Node->Height = false;
		return false;
	}
	if (Node->RightBranch == NULL)
	{
		Node->RightBranch = new (Branch);
		t = Node->RightBranch;
		t->Key = Key;
		t->Height = true;
		t->RightBranch = NULL;
		t->LeftBranch = NULL;
		Node->Height = true;
		return true;
	}

	if (Node->Height == true)
	{
		val = Insert(Key, Node->LeftBranch);
		if (val)
		{
			Node->Height = false;
			return false;
		}
	}
	else
	{
		val = Insert(Key, Node->RightBranch);
		if (val)
		{
			Node->Height = true;
			return true;
		}
	}
}

void Tree::ClearTree(Branch *Node)
{
	if (Node->LeftBranch != NULL) ClearTree(Node->LeftBranch);
	if (Node->RightBranch != NULL) ClearTree(Node->RightBranch);
	delete Node;
}
