#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node
{
	int key;
	unsigned int height;
	Node *Left, *Right;
};
class tree
{
	int tabs;
	Node *Head;
public:
	tree(int );
	tree();
	Node *insert(int, Node *);
	Node *remove(int , Node *);
	void print(Node *);

	Node *FindMin(Node *);
	Node *RemoveMin(Node *);

	int Height(Node *);
	int BalanceFactor(Node *);
	void SetHeight(Node *);
	Node* Balance(Node *);
	Node* RightTurn(Node *);
	Node* LeftTurn(Node *);

	Node *GetHead();
	~tree();
};
tree::tree()
{
	Head = nullptr;
}
tree::tree(int item)
{
	tabs = 0;
	Head = new Node;
	Head->Left = nullptr;
	Head->Right = nullptr;
	Head->key = item;
	Head->height = 1;
}
tree::~tree()
{
	cout << "deconstructor called..." << endl;
}
Node *tree::GetHead()
{
	return Head;
}
int tree::Height(Node *next)
{
	if (next == nullptr)
		return 0;
	return next->height;
}
int tree::BalanceFactor(Node *next)
{
	return Height(next->Right) - Height(next->Left);
}
void tree::SetHeight(Node *next)
{
	unsigned int hLeft = Height(next->Left);
	unsigned int hRight = Height(next->Right);
	if (hRight >= hLeft)
		next->height = hRight + 1;
	else
		next->height = hLeft + 1;
}
Node *tree::RightTurn(Node *next)
{
	// cout << "Right turn called... " << next->key << endl;
	Node *t = next->Right;
	next->Right = t->Left;
	t->Left = next;
	SetHeight(next);
	SetHeight(t);
	if (Head == next)
		Head = t;
	next = t;
	return next;
}
Node *tree::LeftTurn(Node *next)
{
	// cout << "Left turn called... " << next->key << endl;
	Node *t = next->Left;
	next->Left = t->Right;
	t->Right = next;
	SetHeight(next);
	SetHeight(t);
	if (Head == next)
		Head = t;
	next = t;
	return next;
}
Node *tree::Balance(Node *next)
{
	SetHeight(next);
	if (BalanceFactor(next) == 2)
	{
		if (BalanceFactor(next->Right) < 0)
			next->Right = LeftTurn(next->Right);
		next = RightTurn(next);
	}
	if (BalanceFactor(next) == -2)
	{
		if (BalanceFactor(next->Left) > 0)
			next->Left = RightTurn(next->Left);
		next = LeftTurn(next);
	}
	return next;
}
Node *tree::insert(int item, Node *next)
{
	Node *t;
	if (next == nullptr)
	{
		t = new Node;
		t->key = item;
		t->Left = nullptr;
		t->Right = nullptr;
		t->height = 1;
		if (Head == nullptr)
			Head = t;
		return t;
	}
	if (item >= next->key)
	{
		next->Right = insert(item, next->Right);
	}
	else
	{
		next->Left = insert(item, next->Left);
	}
	return Balance(next);
}
void tree::print(Node *next)
{
	if (next == nullptr)
		return;
	tabs++;
	print(next->Left);
	for (int i = 0; i < tabs; i++)
		cout << "  ";
	cout << next->key << endl;
	print(next->Right);
	tabs--;
	return;
}
Node *tree::FindMin(Node *next)
{
	if (next->Left == nullptr)
		return next;
	return FindMin(next->Left);
}
Node *tree::RemoveMin(Node *next)
{
	if (next->Left == nullptr)
		return next->Right;
	next->Left = RemoveMin(next->Left);
	return Balance(next);
}
Node *tree::remove(int item, Node *next)
{
	if (next == nullptr)
		return nullptr;

	if (item > next->key)
		next->Right = remove(item, next->Right);
	if (item < next->key)
		next->Left = remove(item, next->Left);
	if (item == next->key)
	{
		Node *cLeft = next->Left, *cRight = next->Right;
		if (cRight == nullptr)
			return cLeft;
		Node *min = FindMin(cRight);
		min->Right = RemoveMin(cRight);
		min->Left = cLeft;
		if (Head == next)
		{
			Head = Balance(min);
			return Head;
		}
		return Balance(min);
	}
	return Balance(next);
}

///////////////////////////////////////////////////////
void count_elements(Node *next, int &count)
{
	if (next == nullptr)
		return;
	count_elements(next->Left, count);
	count++;
	count_elements(next->Right, count);
}
bool search_left(Node *next, int &delta, Node * (&middle))
{
	bool ans = false;
	if (next->Right != nullptr)
		ans = search_left(next->Right, delta, middle);
	if (ans == true)
		return true;
	middle = next;

	cout << "Delta: " << delta << endl;
	cout << "> " << next->key << endl;

	delta -= 2;
	if (delta <= 1)
	{
		middle = next;
		return true;
	}
	if (next->Left != nullptr)
		return search_left(next->Left, delta, middle);
	return false;
}
bool search_right(Node *next, int &delta, Node * (&middle))
{
	bool ans = false;
	if (next->Left != nullptr)
		ans = search_right(next->Left, delta, middle);
	if (ans == true)
		return true;
	middle = next;

	cout << "Delta: " << delta << endl;
	cout << "> " << next->key << endl;

	delta -= 2;
	if (delta <= 1)
	{
		middle = next;
		return true;
	}
	if (next->Right != nullptr)
		return search_right(next->Right, delta, middle);
	return false;
}
Node *find_middle(Node *Head)
{
	Node *middle = Head;
	int hLeft = 0, hRight = 0, delta;
	count_elements(Head->Left, hLeft);
	count_elements(Head->Right, hRight);
	cout << hLeft << " " << hRight << endl;

	delta = hLeft - hRight;
	if (delta > 1)
		search_left(Head->Left, delta, middle);
	if (delta < -1)
	{
		delta *= -1;
		search_right(Head->Right, delta, middle);
	}
	cout << "Middle element: " << middle->key << endl;
	return middle;
}
int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int a, r_size;
	tree *Avl;
	Node *middle;

	cout << "Enter count of trees: ";
	cin >> a;
	Avl = new tree[a];

	for (int i = 0; i < a; i++)
	{
		r_size = rand() % 20 + 3;
		for (int j = 0; j < r_size; j++)
		{
			Avl[i].insert(rand() % 101 - 50, Avl[i].GetHead());
		}
		cout << "===========================" << endl;
		Avl[i].print(Avl[i].GetHead());
		cout << "---------------------------" << endl;

		middle = find_middle(Avl[i].GetHead());
		cout << "Element which will remove: " << middle->key << endl;
		Avl[i].remove(middle->key, Avl[i].GetHead());

		cout << "---------------------------" << endl;
		Avl[i].print(Avl[i].GetHead());
		cout << "===========================" << endl;
	}
	return 0;
}