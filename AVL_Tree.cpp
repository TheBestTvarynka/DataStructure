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
		tabs = 0;
	}
	void Insert(int);
	void Print();
	void PrintTree(Branch *);
	void PrintSubTree(Branch *);
	Branch *SmallLeftTurn(Branch *);/////////////////////////////
	Branch *SmallRightTurn(Branch *);////////////////////////////
};

int main()
{
	int a, b;
	cin >> a;
	Tree ExampleTree(a);
	ExampleTree.PrintSubTree(ExampleTree.Main);
	while (true)
	{
		cin >> a;
		ExampleTree.Insert(a);
		//ExampleTree.PrintTree(ExampleTree.Main);
		ExampleTree.PrintSubTree(ExampleTree.Main);
	}

	return 0;
}

void Tree::PrintTree(Branch *Node)
{
	if (!Node) return;
	tabs++;

	PrintTree(Node->LeftBrach);

	for (int i = 0; i < tabs; i++) cout << "  ";
	cout << Node->Key << endl;


	PrintTree(Node->RightBranch);

	tabs--;
	return;
}

void Tree::PrintSubTree(Branch *Node)
{
	if (!Node) return;
	tabs++;

	PrintSubTree(Node->LeftBrach);

	for (int i = 0; i < tabs; i++) cout << "  ";
	cout << Node->SubTree << endl;


	PrintSubTree(Node->RightBranch);

	tabs--;
	return;
}

Branch *Tree::SmallLeftTurn(Branch *Position)
{
	int Tmp;
	Branch *tmp;
	Branch *t = Position->RightBranch; //b=t t=b
	t->Parent = Position->Parent;
	Position->Parent = t;
	Position->RightBranch = t->LeftBrach;
	t->LeftBrach = Position;

	Position->SubTree = 0;
	t->SubTree = 0;

	Tmp = t->Key;
	tmp = t;
	t = t->Parent;
	if (t == NULL)
	{
		Main = tmp;
		cout << tmp->Key << " finaly1" << endl;
		PrintTree(tmp);
		return tmp;
	}
	if (Tmp <= t->Key)
	{
		t->LeftBrach = tmp;
		//t->SubTree--;
	}
	else
	{
		t->RightBranch = tmp;
		//t->SubTree++;
	}
	cout << tmp->Key << " finaly" << endl;
	return tmp;
}

Branch *Tree::SmallRightTurn(Branch *Position)
{
	cout<<"Small right turn"<<endl;
	int Tmp;
	Branch *tmp;
	Branch *t = Position->LeftBrach; //b=t t=b
	t->Parent = Position->Parent;
	Position->Parent = t;
	Position->LeftBrach = t->RightBranch;
	t->RightBranch = Position;

	Position->SubTree = 0;
	t->SubTree = 0;

	Tmp = t->Key;
	tmp = t;
	t = t->Parent;
	if (t == NULL)
	{
		Main = tmp;
		cout << tmp->Key << " finaly1" << endl;
		//PrintTree(tmp);
		return tmp;
	}
	if (Tmp <= t->Key)
	{
		t->LeftBrach = tmp;
		//t->SubTree--;
	}
	else
	{
		t->RightBranch = tmp;
		//t->SubTree++;
	}
	cout << tmp->Key << " finaly" << endl;
	return tmp;
}

void Tree::Insert(int Key)
{
	Branch *t = Main, *Position;
	Position = t;
	int Value;

	while (t != NULL)
	{
		//cout << "LOL" << endl;
		Position = t;
		if (t->Key <= Key)
		{
			//cout << "Right" << endl;
			t = t->RightBranch;
		}
		else
		{
			//cout << "Left" << endl;
			t = t->LeftBrach;
		}
	}//при виході p - вказівник на останній елемент (листок)
	t = Position;//вказівник на оастанній
	if (Position->Key <= Key)
	{
		Position->SubTree++;
		Position->RightBranch = new Branch;
		Position = Position->RightBranch;
	}
	else
	{
		Position->SubTree--;
		Position->LeftBrach = new Branch;
		Position = Position->LeftBrach;
	}
	Position->Parent = t;
	Position->RightBranch = NULL;
	Position->LeftBrach = NULL;
	Position->Key = Key;
	Position->SubTree = 0;//ми додали ключ де треба. Тепер збалансуємо дерево

	if (t->SubTree == 0) return;
	//
	Value = t->Key;
	Position = t->Parent;
	while (Position != NULL)// (Position->Parent != NULL)
	{
		if (Value < Position->Key)//отже це ліва дитина
		{
			Position->SubTree--;
			if (Position->SubTree <= -2)//завелика висота. Балансуєм
			{
				if (Key <= Value)
				{
					Position = SmallRightTurn(Position);
					if (Position->SubTree == 0)
					{
						// cout << "Exit 1" << endl;
						PrintTree(Main);
						PrintSubTree(Main);
						// cout << "Exit 2" << endl;
						return;
					}
					PrintTree(Main);
					PrintSubTree(Main);
				}
				else
				{
					
				}
			}
		}
		else//права дитина
		{
			Position->SubTree++;
			if (Position->SubTree >= 2)//завелика висота. Балансуєм
			{
				if (Key >= Value)
				{
					// cout << "SmallLeftTurn start in posiiton " << Position->Key << endl;
					Position = SmallLeftTurn(Position);
					if (Position->SubTree == 0)
					{
						// cout << "Exit 1" << endl;
						// PrintTree(Main);
						// PrintSubTree(Main);
						// cout << "Exit 2" << endl;
						return;
					}
					PrintTree(Main);
					PrintSubTree(Main);
					// cout << "SmallLeftTurn end" << endl;
				}
				else//це великий лівий поворот
				{
					Position = SmallRightTurn();
					Position = SmallLeftTurn();
				}
			}
		}
		Value = Position->Key;
		// t = Position;
		Position = Position->Parent;
	}
}
