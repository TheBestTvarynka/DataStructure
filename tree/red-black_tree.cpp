#include <iostream>

using namespace std;

struct Node
{
	int value;
	// false - black
	// true - red
	bool color;
	Node *Right, *Left, *Parent;
};

class RBTree
{
	Node *Head;
	int tabs;
public:
	RBTree(int item);
	RBTree();
	void insert(int);
	void print(Node *);

	Node *GetHead();
	void Balance(Node *);
	Node *LeftTurn(Node *);
	Node *RightTurn(Node *);
	// ~RBTree();
};
RBTree::RBTree(int item)
{
	tabs = 0;
	Head = new Node;
	Head->value = item;
	Head->color = false;
	Head->Left = Head->Right = nullptr;
	Head->Parent = nullptr;
}
RBTree::RBTree()
{
	tabs = 0;
	Head = nullptr;
}
Node *RBTree::GetHead()
{
	return Head;
}
void RBTree::print(Node *next)
{
	if (next == nullptr)
		return;
	tabs++;
	print(next->Left);

	for (int i = 0; i < tabs; i++)
		cout << "  ";
	cout << next->value << endl;

	print(next->Right);
	tabs--;

	return;
}
void RBTree::insert(int item)
{
	if (Head == nullptr)
	{
		Head = new Node;
		Head->value = item;
		Head->color = false;
		Head->Left = Head->Right = nullptr;
		Head->Parent = nullptr;
		return;
	}

	Node *t = Head, *p;
	while (t != nullptr)
	{
		p = t;
		if (t->value >= item)
			t = t->Left;
		else
			t = t->Right;
	}
	// cout << "parent of finding node: " << p->value << endl;
	t = new Node;
	t->value = item;
	t->color = true;
	t->Right = t->Left = nullptr;
	t->Parent = p;
	if (p->value > item)
		p->Left = t;
	else
		p->Right = t;
	// cout << "we allocated memory for new element..." << endl;
	Balance(t);
}
void RBTree::Balance(Node *next)
{
	cout << "created element: " << next->value << endl;
	if ((next->Parent)->color == false || (next->Parent)->Parent == nullptr)
		return;
	Node *locRoot = next->Parent;
	Node *t = next;

	cout << "locRoot: " << (locRoot->Parent)->value << endl;

	while (locRoot->color != false)
	{
		locRoot = locRoot->Parent;
		if (locRoot->value > t->value)
		{
			if (t->value >= (t->Parent)->value)
			{
				t = RightTurn(t->Parent);
				locRoot = t->Parent;
			}
			if (locRoot->Right != nullptr && (locRoot->Right)->color == true)
			{
				(locRoot->Right)->color = false;
				(locRoot->Left)->color = false;
				if (locRoot != Head)
					locRoot->color = true;
			}
			else
			{
				locRoot = LeftTurn(locRoot);
				locRoot->color = false;
				(locRoot->Right)->color = true;
			}
		}
		else
		{
			cout << "I am here... What a pity..." << endl;
		}
		t = locRoot;
		locRoot = locRoot->Parent;
		if (locRoot == nullptr || locRoot->color == false || t->color == false)
			break;
	}
}
// need to check
Node *RBTree::LeftTurn(Node *next)
{
	Node *t = next->Left;
	t->Parent = next->Parent;
	next->Left = t->Right;
	t->Right = next;
	next->Parent = t;
	if (next == Head)
	{
		Head = t;
		return t;
	}
	if ((t->Parent)->value > t->value) {
		(t->Parent)->Left = t;
	}
	else {
		(t->Parent)->Right = t;
	}
	return t;
}
// need to check
Node *RBTree::RightTurn(Node *next)
{
	Node *t = next->Right;
	t->Parent = next->Parent;
	next->Right = t->Left;
	t->Left = next;
	next->Parent = t;
	if (next == Head)
	{
		Head = t;
		return t;
	}
	if ((t->Parent)->value > t->value)
		(t->Parent)->Left = t;
	else
		(t->Parent)->Right = t;
	return t;
}

int main()
{
	RBTree a(20);
	Node *temp;
	int item;

	a.print(a.GetHead());
	cin >> item;
	while (item != 0)
	{
		a.insert(item);
		temp = a.GetHead();
		a.print(temp);
		cin >> item;
	}
	return 0;
}
