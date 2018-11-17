#include <iostream>
using namespace std;

struct Branch
{
	int Key;
	int SubTree;
	Branch *LeftBranch, *RightBranch;
	Branch *Parent;
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
		Main->Parent = NULL;
		Main->Key = Key;
		Main->SubTree = 0;
		tabs = 0;
	}
	void Insert(int);
	void Remove(int);
	void PrintTree(Branch *);
	void BalanceArrangement(Branch *);
	Branch *SmallLeftTurn(Branch *);
	Branch *SmallRightTurn(Branch *);
	void ClearTree(Branch *);
};

int main()
{
	int a, b;

	cin >> a;
	Tree ExampleTree(a);
	ExampleTree.PrintTree(ExampleTree.Main);
	ExampleTree.Insert(a);
	ExampleTree.Remove(a);
	
	ExampleTree.ClearTree(ExampleTree.Main);
	return 0;
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

Branch *Tree::SmallLeftTurn(Branch *Position)
{
	int Tmp;
	Branch *tmp;
	Branch *t = Position->RightBranch; //b=t t=b
	t->Parent = Position->Parent;
	Position->Parent = t;
	Position->RightBranch = t->LeftBranch;
	t->LeftBranch = Position;

	Tmp = t->Key;
	tmp = t;
	t = t->Parent;
	if (t == NULL)
	{
		Main = tmp;
		return tmp;
	}
	if (Tmp <= t->Key) t->LeftBranch = tmp;
	else t->RightBranch = tmp;

	return tmp;
}

Branch *Tree::SmallRightTurn(Branch *Position)
{
	int Tmp;
	Branch *tmp;
	Branch *t = Position->LeftBranch; //b=t t=b
	t->Parent = Position->Parent;
	Position->Parent = t;
	Position->LeftBranch = t->RightBranch;
	t->RightBranch = Position;

	Tmp = t->Key;
	tmp = t;
	t = t->Parent;
	if (t == NULL)
	{
		Main = tmp;
		return tmp;
	}
	if (Tmp <= t->Key) t->LeftBranch = tmp;
	else t->RightBranch = tmp;

	return tmp;
}

void Tree::BalanceArrangement(Branch *Position)
{
	if (Position->SubTree == 0)
	{
		(Position->LeftBranch)->SubTree = 0;
		(Position->RightBranch)->SubTree = 0;
	}
	if (Position->SubTree == 1)
	{
		(Position->LeftBranch)->SubTree = -1;
		(Position->RightBranch)->SubTree = 0;
	}
	if (Position->SubTree == -1)
	{
		(Position->LeftBranch)->SubTree = 0;
		(Position->RightBranch)->SubTree = 1;
	}
	Position->SubTree = 0;
}

void Tree::Insert(int Key)//Ð¼Ð¾Ð¶Ð»Ð¸Ð²Ð¾ Ð¼Ð¾Ð¶Ð½Ð° Ð¾Ð¿Ñ‚Ð¸Ð¼Ñ–Ð·ÑƒÐ²Ð°Ñ‚Ð¸ Ð²Ð»Ð°ÑÐ½Ðµ Ð²ÑÑ‚Ð°Ð²ÐºÑƒ
{
	Branch *t = Main, *Position;
	int Value;

	while (t != NULL)
	{
		Position = t;
		if (t->Key <= Key) t = t->RightBranch;
		else t = t->LeftBranch;
	}//Ð¿Ñ€Ð¸ Ð²Ð¸Ñ…Ð¾Ð´Ñ– p - Ð²ÐºÐ°Ð·Ñ–Ð²Ð½Ð¸Ðº Ð½Ð° Ð¾ÑÑ‚Ð°Ð½Ð½Ñ–Ð¹ ÐµÐ»ÐµÐ¼ÐµÐ½Ñ‚ (Ð»Ð¸ÑÑ‚Ð¾Ðº)

	t = Position;//Ð²ÐºÐ°Ð·Ñ–Ð²Ð½Ð¸Ðº Ð½Ð° Ð¾Ð°ÑÑ‚Ð°Ð½Ð½Ñ–Ð¹
	if (Position->Key <= Key)
	{
		Position->SubTree++;
		Position->RightBranch = new Branch;
		Position = Position->RightBranch;
	}
	else
	{
		Position->SubTree--;
		Position->LeftBranch = new Branch;
		Position = Position->LeftBranch;
	}
	Position->Parent = t;
	Position->RightBranch = NULL;
	Position->LeftBranch = NULL;
	Position->Key = Key;
	Position->SubTree = 0;//Ð¼Ð¸ Ð´Ð¾Ð´Ð°Ð»Ð¸ ÐºÐ»ÑŽÑ‡ Ð´Ðµ Ñ‚Ñ€ÐµÐ±Ð°. Ð¢ÐµÐ¿ÐµÑ€ Ð·Ð±Ð°Ð»Ð°Ð½ÑÑƒÑ”Ð¼Ð¾ Ð´ÐµÑ€ÐµÐ²Ð¾

	if (t->SubTree == 0) return;
	Value = t->Key;
	Position = t->Parent;
	while (Position != NULL)// (Position->Parent != NULL)
	{
		if (Value < Position->Key)//Ð¾Ñ‚Ð¶Ðµ Ñ†Ðµ Ð»Ñ–Ð²Ð° Ð´Ð¸Ñ‚Ð¸Ð½Ð°
		{
			Position->SubTree--;
			if (Position->SubTree == 0) return;//Ð·Ð½Ð°Ñ‡Ð¸Ñ‚ÑŒ Ð¼Ð¸ Ð·Ð±Ð°Ð»Ð°Ð½ÑÑƒÐ²Ð°Ð»Ð¸ Ñ†Ðµ Ð¿Ñ–Ð´Ð´ÐµÑ€ÐµÐ²Ð¾. Ð’Ð¸Ñ…Ñ–Ð´
			if (Position->SubTree == -2)//Ð·Ð°Ð²ÐµÐ»Ð¸ÐºÐ° Ð²Ð¸ÑÐ¾Ñ‚Ð°. Ð‘Ð°Ð»Ð°Ð½ÑÑƒÑ”Ð¼
			{
				if (Key <= Value)//Ð¼Ð°Ð»Ð¸Ð¹ Ð¿Ð¾Ð²Ð¾Ñ€Ð¾Ñ‚
				{
					Position = SmallRightTurn(Position);
					Position->SubTree = 0;
					(Position->RightBranch)->SubTree = 0;
				}
				else//Ð²ÐµÐ»Ð¸ÐºÐ¸Ð¹ Ð¿Ð¾Ð²Ð¾Ñ€Ð¾Ñ‚
				{
					Position = SmallLeftTurn(Position->LeftBranch);
					Position = SmallRightTurn(Position->Parent);
					BalanceArrangement(Position);
				}
				return;
			}
		}
		else//Ð¿Ñ€Ð°Ð²Ð° Ð´Ð¸Ñ‚Ð¸Ð½Ð°
		{
			Position->SubTree++;
			if (Position->SubTree == 0) return;//Ð·Ð½Ð°Ñ‡Ð¸Ñ‚ÑŒ Ñ†Ðµ Ð¿Ñ–Ð´Ð´ÐµÑ€ÐµÐ²Ð¾ ÑÑ‚Ð°Ð»Ð¾ Ð·Ð±Ð°Ð»Ð°Ð½ÑÐ¾Ð²Ð°Ð½Ðµ
			if (Position->SubTree == 2)//Ð·Ð°Ð²ÐµÐ»Ð¸ÐºÐ° Ð²Ð¸ÑÐ¾Ñ‚Ð°. Ð‘Ð°Ð»Ð°Ð½ÑÑƒÑ”Ð¼
			{
				if (Key >= Value)
				{
					Position = SmallLeftTurn(Position);
					Position->SubTree = 0;
					(Position->LeftBranch)->SubTree = 0;
				}
				else//Ñ†Ðµ Ð²ÐµÐ»Ð¸ÐºÐ¸Ð¹ Ð»Ñ–Ð²Ð¸Ð¹ Ð¿Ð¾Ð²Ð¾Ñ€Ð¾Ñ‚
				{
					Position = SmallRightTurn(Position->RightBranch);
					Position = SmallLeftTurn(Position->Parent);
					BalanceArrangement(Position);
				}
				return;
			}
		}
		Value = Position->Key;
		Position = Position->Parent;
	}
}

void Tree::Remove(int Key)
{
	Branch *p = Main, *t = Main;
	int Value;

	while (t != NULL && t->Key != Key)
	{
		if (Key >= t->Key) t = t->RightBranch;
		else t = t->LeftBranch;
	}

	if (t == NULL) return;
	p = t;
	if (p->RightBranch == NULL)
	{
		if ((p->Parent)->Key <= p->Key)
			(p->Parent)->RightBranch = p->LeftBranch;
		else
			(p->Parent)->LeftBranch = p->LeftBranch;
		t = p->Parent;
		if (p->LeftBranch != NULL)
			(p->LeftBranch)->Parent = p->Parent;
		delete p;
		Value = Key;
	}
	else
	{
		p = t->RightBranch;
		while (p->LeftBranch != NULL)
		{
			p = p->LeftBranch;
		}
		t->Key = p->Key;
		Value = p->Key;
		if (p == t->RightBranch)
			(p->Parent)->RightBranch = p->RightBranch;
		else
			(p->Parent)->LeftBranch = p->RightBranch;
		if (p->RightBranch != NULL) (p->RightBranch)->Parent = p->Parent;
		t = p->Parent;
		delete p;
	}
	
	while (t != NULL)
	{
		if (t->Key <= Value)
		{
			t->SubTree--;
			if (t->SubTree == -1) return;
			if (t->SubTree == -2)//Ð±Ð°Ð»Ð°Ð½ÑÑƒÑ”Ð¼Ð¾
			{
				if ((t->LeftBranch)->SubTree == 1)//Ð²ÐµÐ»Ð¸ÐºÐ¸Ð¹ Ð¿Ð¾Ð²Ð¾Ñ€Ð¾Ñ‚
				{

					t = SmallLeftTurn(t->LeftBranch);
					t = SmallRightTurn(t->Parent);
					BalanceArrangement(t);
				}
				else//Ð¼Ð°Ð»Ð¸Ð¹ Ð¿Ð¾Ð²Ð¾Ñ€Ð¾Ñ‚
				{
					t = SmallRightTurn(t);
					if (t->SubTree == -1)
					{
						t->SubTree = 0;
						(t->RightBranch)->SubTree = 0;
					}
					else
					{
						t->SubTree = 1;
						(t->RightBranch)->SubTree = -1;
						return;
					}
				}
			}
		}
		else
		{
			t->SubTree++;
			if (t->SubTree == 1) return;
			if (t->SubTree == 2)
			{
				if ((t->RightBranch)->SubTree == -1)//Ð²ÐµÐ»Ð¸ÐºÐ¸Ð¹ Ð¿Ð¾Ð²Ð¾Ñ€Ð¾Ñ‚
				{
					t = SmallRightTurn(t->RightBranch);
					t = SmallLeftTurn(t->Parent);
					BalanceArrangement(t);
				}
				else
				{
					t = SmallLeftTurn(t);
					if (t->SubTree == 1)
					{
						t->SubTree = 0;
						(t->LeftBranch)->SubTree = 0;
					}
					else
					{
						t->SubTree = -1;
						(t->LeftBranch)->SubTree = 1;
						return;
					}
				}
			}
		}
		Value = t->Key;
		t = t->Parent;
	}
}

void Tree::ClearTree(Branch *Node)
{
	if (Node->LeftBranch != NULL) ClearTree(Node->LeftBranch);
	if (Node->RightBranch != NULL) ClearTree(Node->RightBranch);
	delete Node;
}
