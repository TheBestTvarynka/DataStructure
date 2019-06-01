#include <iostream>

using namespace std;

template <typename T, typename P>
struct Node
{
	T value;
	P priority;
	Node *Next;
};

template <typename T, typename P>
class queue_priority
{
	Node<T, P> *Head;
public:
	queue_priority();
	void push(T, P);
	bool pop(T &);
	bool pop_priority(P &);
	int size();
	bool isEmpty();
	void del_back(T &, P &);
	void erase(T &);
	void print();
	void clear();
	~queue_priority();
};
template <typename T, typename P>
void queue_priority<T, P>::clear()
{
	Node<T, P> *t = Head->Next, *p = Head;
	while (t != nullptr)
	{
		delete p;
		p = t;
		t = t->Next;
	}
	Head = new (Node<T, P>);
	Head->Next = nullptr;
}
template <typename T, typename P>
void queue_priority<T, P>::erase(T &item)
{
	Node<T, P> *t = Head->Next, *p = Head;
	while (t != nullptr && t->value != item)
	{
		p = t;
		t = t->Next;
	}
	if (t == nullptr)
		return;
	p->Next = t->Next;
	delete t;
}
template <typename T, typename P>
void queue_priority<T, P>::del_back(T &value, P &priority)
{
	if (isEmpty())
		return;
	Node<T, P> *t = Head->Next;
	value = t->value;
	priority = t->priority;
	Head->Next = t->Next;
	delete t;
}
template <typename T, typename P>
queue_priority<T, P>::queue_priority()
{
	Head = new (Node<T, P>);
	Head->Next = nullptr;
}
template <typename T, typename P>
queue_priority<T, P>::~queue_priority()
{
	Node<T, P> *t = Head->Next, *p;
	delete Head;
	while (t != nullptr)
	{
		p = t;
		t = t->Next;
		delete p;
	}
}
template <typename T, typename P>
void queue_priority<T, P>::push(T item, P prio)
{
	Node<T, P> *t = new (Node<T, P>);
	t->value = item;
	t->priority = prio;

	Node<T, P> *p = Head;
	while (p->Next != nullptr && (p->Next)->priority >= prio)
	{
		if ((p->Next)->priority == prio && item == (p->Next)->value)
		{
			return;
		}
		p = p->Next;
	}
	t->Next = p->Next;
	p->Next = t;
}
template <typename T, typename P>
bool queue_priority<T, P>::pop(T &out)
{
	if (isEmpty())
		return false;
	Node<T, P> *t = Head->Next;
	out = t->value;
	Head->Next = t->Next;
	delete t;
	return true;
}
template <typename T, typename P>
bool queue_priority<T, P>::pop_priority(P &out)
{
	if (isEmpty())
		return false;
	Node<T, P> *t = Head->Next;
	out = t->priority;
	return true;
}
template <typename T, typename P>
bool queue_priority<T, P>::isEmpty()
{
	if (Head->Next == nullptr)
		return true;
	return false;
}
template <typename T, typename P>
int queue_priority<T, P>::size()
{
	Node<T, P> *t = Head->Next;
	int count = 0;
	while (t != nullptr)
	{
		t = t->Next;
		count++;
	}
	return count;
}
template <typename T, typename P>
void queue_priority<T, P>::print()
{
	Node<T, P> *t = Head->Next;
	while (t != nullptr)
	{
		cout << t->value << " ";
		t = t->Next;
	}
	cout << endl;
}

// int main(int argc, char const *argv[])
// {
//     queue_priority<char, float> a;
//     a.push('f', 5.6);
//     a.push('a', 5.2);
//     a.push('c', 5.9);
//     a.push('k', 5.7);
//     a.print();
//     return 0;
// }