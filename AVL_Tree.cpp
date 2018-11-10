#include <iostream>

using namespace std;

struct Branch
{
	int Key;
	int SubTree;
	Branch *LeftBrach, *RightBranch;
	Branch *Parent;
};

class Tree
{
	int tabs;
	//Branch *Position;
public:
	Branch *Main;
	Tree(int Key)
	{
		Main = new (Branch);
		Main->LeftBrach = NULL;
		Main->RightBranch = NULL;
		Main->Parent = NULL;
		Main->Key = Key;
		Main->SubTree = 0;
		tabs=0;
	}
	void Insert(int);
	void Print();
	void PrintTree(Branch *);
	Branch *SmallLeftTurn(Branch *);/////////////////////////////
	//Branch *SmallRightTurn(Branch *);////////////////////////////
};

int main()
{
	int a, b;
	cin >> a;
	Tree ExampleTree(a);
	ExampleTree.PrintTree(ExampleTree.Main);
	while(true)
	{
		cin >> a;
		ExampleTree.Insert(a);	
		ExampleTree.PrintTree(ExampleTree.Main);
	}
	
	return 0;
}

// void Tree::PrintTree(Branch *Node)
// {
// 	if (Node != NULL)
// 	{
// 		PrintTree(Node->LeftBrach);
// 		cout << Node->Key << " ";
// 		PrintTree(Node->RightBranch);
// 	}
// }

void Tree::PrintTree(Branch *aBranch)
{
	if (!aBranch) return;
	tabs++;

	PrintTree(aBranch->LeftBrach);

	for (int i = 0; i < tabs; i++) cout << "  ";
	cout << aBranch->Key << endl;


	PrintTree(aBranch->RightBranch);

	tabs--;
	return;
}

Branch *Tree::SmallLeftTurn(Branch *Position)
{
	int Tmp;
	Branch *tmp;
	Branch *t = Position->RightBranch; //b=t t=b
	Position->RightBranch = t->LeftBrach;
	tmp = t->LeftBrach;
	tmp->Parent = Position;
	t->LeftBrach = Position;
	t->Parent = Position->Parent;
	Position->Parent = t;
	Position->SubTree = 0;
	t->SubTree = 1;

	Tmp = t->Key;
	tmp = t;
	t = t->Parent;
	if (Tmp <= t->Key)
	{
		t->LeftBrach = tmp;
		t->SubTree--;
	}
	else
	{
		t->RightBranch = tmp;
		t->SubTree++;
	}
	return tmp;
}

void Tree::Insert(int Key)
{
	Branch *t = Main, *Position;
	Position = t;
	int Value;

	while (t != NULL)
	{
		cout << "LOL" << endl;
		Position = t;
		if (t->Key <= Key)
		{
			cout << "Right" << endl;
			t = t->RightBranch;
		}
		else
		{
			cout << "Left" << endl;
			t = t->LeftBrach;
		}
	}//при виході p - вказівник на останній елемент (листок)
	t = Position;
	if (Position->Key <= Key)
	{
		Position->RightBranch = new Branch;
		Position = Position->RightBranch;
	}
	else
	{
		Position->LeftBrach = new Branch;
		Position = Position->LeftBrach;
	}
	Position->Parent = t;
	Position->RightBranch = NULL;
	Position->LeftBrach = NULL;
	Position->Key = Key;
	Position->SubTree = 0;//ми додали ключ де треба. Тепер збалансуємо дерево

	// Position
	/*t = Position;
	Position = Position->Parent;
	Value = Position->Key;
	while (true)// (Position->Parent != NULL)
	{
		Position = Position->Parent;
		if (Value < Position->Key)//отже це ліва дитина
		{
			Position->SubTree--;
			if (Position->SubTree <= -2)//завелика висота. Балансуєм
			{
				/*if (Value >= t->Key) SmallRightTurn(Position);
				else //це великий правий поворот
				{

				}
			}
		}
		else//права дитина
		{
			Position->SubTree++;
			if (Position->SubTree >= 2)//завелика висота. Балансуєм
			{
				if (Value <= t->Key) Position = SmallLeftTurn(Position);
				else//це великий правий поворот
				{

				}
			}
		}
		Value = Position->Key;
		Position = Position->Parent;
	}*/
}

void Tree::Print()
{
	// Branch *t = Main, *P;
	// cout << t->Key << " ";
	// P = t;
	// P = P->RightBranch;
	// cout << P->Key << " ";
	// P = P->RightBranch;
	// cout << P->Key << " ";
	// t = t->LeftBrach;
	// cout << t->Key << endl;
	//PrintTree()
}
