#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

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
	int count_of_rotatins;
	RBTree(int item);
	RBTree();
	
	void insert(int);
	void remove(int);
	void print(Node *);

	Node *GetHead();
	void BalanceInsert(Node *);
	void BalanceDelete(Node *, int);
	Node *LeftTurn(Node *);
	Node *RightTurn(Node *);
	void Clear(Node *);
	~RBTree();
};
RBTree::RBTree(int item)
{
	count_of_rotatins = 0;
	tabs = 0;
	Head = new Node;
	Head->value = item;
	Head->color = false;
	Head->Left = Head->Right = nullptr;
	Head->Parent = nullptr;
}
RBTree::RBTree()
{
	count_of_rotatins = 0;
	tabs = 0;
	Head = nullptr;
}
RBTree::~RBTree()
{
	Clear(Head);
}
void RBTree::Clear(Node *next)
{
	if (next == nullptr)
		return;
	if (next->Left != nullptr)
		Clear(next->Left);
	if (next->Right != nullptr)
		Clear(next->Right);
	delete next;
	return;
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
		if (t->value > item)
			t = t->Left;
		else
			t = t->Right;
	}
	t = new Node;
	t->value = item;
	t->color = true;
	t->Right = t->Left = nullptr;
	t->Parent = p;
	if (p->value > item)
		p->Left = t;
	else
		p->Right = t;
	BalanceInsert(t);
}
void RBTree::BalanceInsert(Node *next)
{
	if ((next->Parent)->color == false || (next->Parent)->Parent == nullptr)
		return;
	Node *locRoot = next->Parent;
	Node *t = next;

	while (locRoot->color != false)
	{

		locRoot = locRoot->Parent;
		if (locRoot->value > t->value)
		{
			if (locRoot->Right != nullptr && (locRoot->Right)->color == true)
			{
				locRoot->color = true;
				(locRoot->Left)->color = false;
				(locRoot->Right)->color = false;
			}
			else
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
		}
		else
		{
			if (locRoot->Left != nullptr && (locRoot->Left)->color == true)
			{
				locRoot->color = true;
				(locRoot->Left)->color = false;
				(locRoot->Right)->color = false;
			}
			else
			{
				if (t->value < (t->Parent)->value)
				{
					t = LeftTurn(t->Parent);
					locRoot = t->Parent;
				}
				if (locRoot->Left != nullptr && (locRoot->Left)->color == true)
				{
					(locRoot->Left)->color = false;
					(locRoot->Right)->color = false;
					if (locRoot != Head)
						locRoot->color = true;
				}
				else
				{
					locRoot = RightTurn(locRoot);
					locRoot->color = false;
					(locRoot->Left)->color = true;
				}
			}
		}
		t = locRoot;
		locRoot = locRoot->Parent;
		if (locRoot == nullptr || locRoot == Head || locRoot->color == false || (locRoot->Parent)->color == false)
			break;
	}
}
Node *RBTree::LeftTurn(Node *next)
{
	Node *t = next->Left;
	t->Parent = next->Parent;
	next->Left = t->Right;
	if (t->Right != nullptr)
		(next->Left)->Parent = next;
	t->Right = next;
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
Node *RBTree::RightTurn(Node *next)
{
	Node *t = next->Right;
	t->Parent = next->Parent;
	next->Right = t->Left;
	if (t->Left != nullptr)
		(next->Right)->Parent = next;
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
void RBTree::remove(int item)
{
	int key;
	Node *t = Head;
	Node *p = nullptr;
	
	while (t->value != item)
	{
		if (t->value <= item)
			t = t->Right;
		else
			t = t->Left;
		if (t == nullptr)
		{
			cout << "Element not exist..." << endl;
			return;
		}
	}
	// if t haven't any children
	if (t->Right == nullptr && t->Left == nullptr)
	{
		if ((t->Parent)->value > t->value)
			(t->Parent)->Left = nullptr;
		else
			(t->Parent)->Right = nullptr;
		key = t->value;
		cout << "deleted node have not any children... her Parent: " << (t->Parent)->value << endl;
		if (t->color == false)
		{
			cout << "it is black..." << endl;
			BalanceDelete(t->Parent, key);
		}
		delete t;
		return;
	}
	// 
	if (t->Right != nullptr)
	{
		// then we find alternative element
		p = t->Right;
		cout << "enter point: " << p->value << endl;
		while (p->Left != nullptr)
			p = p->Left;
		t->value = p->value;
		t = p;
		// cout << "alternative value: " << t->value << endl;
		// cout << "------------------------" << endl;
		// print(Head);
		// cout << "------------------------" << endl;
		if (t->value < (t->Parent)->value)
			(t->Parent)->Left = t->Right;
		else
			(t->Parent)->Right = t->Right;
		if (t->Right != nullptr)
			(t->Right)->Parent = t->Parent;
	}
	else
	{
		cout << "we went in hell..." << endl;
		if (t->value < (t->Parent)->value)
			(t->Parent)->Left = t->Left;
		else
			(t->Parent)->Right = t->Left;
		(t->Left)->Parent = t->Parent;
	}
	// if deleted node is red then we just delete them
	if (t->color == true)
	{
		delete t;
		return;
	}
	// if right child is red then we just repaint them
	if (t->Right != nullptr && (t->Right)->color == true)
	{
		(t->Right)->color = false;
		delete t;
		return;
	}
	if (t->Left != nullptr && (t->Left)->color == true)
	{
		(t->Left)->color = false;
		delete t;
		return;
	}
	// also we have two black node, what a pity. Balancing
	p = t;
	key = t->value;
	t = t->Parent;
	delete p;
	BalanceDelete(t, key);
}
void RBTree::BalanceDelete(Node *next, int key)
{
	cout << "balancing called with arguments: " << next->value << " " << key << endl;
	Node *t;
	if (key < next->value)
	{
		t = next->Right;
		if (t->color == true)
		{
			// simple case when brother is red
			t = RightTurn(next);
			t->color = false;
			next->color = true;
			// need to check
			BalanceDelete(next, key);
		}
		else
		{
			cout << "brother is black..." << endl;
			// brother is black
			// both is red
			if (t->Right != nullptr && t->Left != nullptr && (t->Right)->color == true && (t->Left)->color == true)
			{
				// need to check
				cout << "both child is red..." << endl;
				t = RightTurn(next);
				t->color = next->color;
				next->color = false;
				(t->Right)->color = false;
				return;
			}
			// both is black
			if ((t->Right == nullptr && t->Left == nullptr))
			{
				cout << "both child is black -> null-lifs..." << endl;
				t->color = true;
				next->color = false;
				return;
			}
			if (t->Right != nullptr && t->Left != nullptr && (t->Right)->color == false && (t->Left)->color == false)
			{
				cout << "both child is black -> lifs exist..." << endl;
				t->color = true;
				t = RightTurn(t);
				t->color = next->color;
				next->color = true;
				(t->Right)->color = false;
				BalanceDelete(next, key);
				return;
			}
			cout << "we in last case..." << endl;
			if (t->Left != nullptr && (t->Left)->color == true)
			{
				cout << "left child is red..." << endl;
				t = LeftTurn(t);
				cout << "after first rotation: " << endl;
				// cout << "------------------------" << endl;
				// print(Head);
				// cout << "------------------------" << endl;
			}
			cout << "value of axis point: " << next->value << " " << t->value << endl;
			t = RightTurn(next);

			cout << "after second rotation: " << endl;
			// cout << "------------------------" << endl;
			// print(Head);
			// cout << "------------------------" << endl;
			
			t->color = next->color;
			next->color = false;
			(t->Right)->color = false;
		}
	}
	else
	{
		t = next->Right;
		cout << "Another half of algorithm..." << endl;
	}
}
int main()
{
	srand(time(NULL));

	RBTree a(20);
	Node *temp;
	int item;
	vector<int> input(20000);

	a.print(a.GetHead());

	for (int i = 0; i < 20000; ++i)
	{
		input[i] = rand() % 100000;
		cout << input[i] << " ";
		// cin >> input[i];
	}
	cout << endl;
	for (int j = 0; j < 20000; ++j)
	{
		temp = a.GetHead();
		a.insert(input[j]);
		// a.print(temp);
	}
	// cout << a.count_of_rotatins << endl;
	// item = 1;
	// cin >> item;
	// while (item != 0)
	// {
	// 	a.remove(item);
	// 	temp = a.GetHead();
	// 	a.print(temp);
	// 	cin >> item;
	// }
	return 0;
}
