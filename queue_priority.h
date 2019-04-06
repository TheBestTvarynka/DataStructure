#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T value;
	unsigned int priority;
	Node *Next;
};

template <typename T>
class queue_priority
{
	Node<T> *Head;
public:
	queue_priority();
	void push(T, int);
	bool pop(T &);
	bool pop_priority(int &);
	int size();
	bool isEmpty();
	void print();
	~queue_priority();
};
template <typename T>
queue_priority<T>::queue_priority()
{
	Head = new (Node<T>);
	Head->Next = nullptr;
}
template <typename T>
queue_priority<T>::~queue_priority()
{
	Node<T> *t = Head->Next, *p;
	delete Head;
	while(t != nullptr)
	{
		p = t;
		t = t->Next;
		delete p;
	}
}
template <typename T>
void queue_priority<T>::push(T item, int prio)
{
	Node<T> *t = new (Node<T>);
	t->value = item;
	t->priority = prio;

	Node<T> *p = Head;
	while (p->Next != nullptr && (p->Next)->priority <= prio)
		p = p->Next;
	t->Next = p->Next;
	p->Next = t;
}
template <typename T>
bool queue_priority<T>::pop(T &out)
{
	if (isEmpty())
		return false;
	Node<T> *t = Head->Next;
	out = t->value;
	Head->Next = t->Next;
	delete t;
	return true;
}
template <typename T>
bool queue_priority<T>::pop_priority(int &out)
{
	if (isEmpty())
		return false;
	Node<T> *t = Head->Next;
	out = t->priority;
	return true;
}
template <typename T>
bool queue_priority<T>::isEmpty()
{
	if (Head->Next == nullptr)
		return true;
	return false;
}
template <typename T>
int queue_priority<T>::size()
{
	Node<T> *t = Head->Next;
	int count = 0;
	while (t != nullptr)
	{
		t = t->Next;
		count++;
	}
	return count;
}
template <typename T>
void queue_priority<T>::print()
{
	Node<T> *t = Head->Next;
	while (t != nullptr)
	{
		cout << t->value << " ";
		t = t->Next;
	}
	cout << endl;
}

// int main(int argc, char const *argv[])
// {
// 	queue_priority<char> a;
// 	a.push('f', 5);
// 	a.push('a', 5);
// 	a.push('c', 5);
// 	a.push('k', 5);
// 	a.print();
// 	return 0;
// }