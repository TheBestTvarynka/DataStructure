#include <iostream>

using namespace std;

class Stack
{
    int *ArrayStack;
    int Size;
    int top;
public:
    Stack();
    void push(int );
    int pop();
    void print();
    void resize(int );
    ~Stack();
};

int main()
{
    Stack A;
    int a = 1;
    while (a != 0)
    {
        cin >> a;
        A.push(a);
        A.print();
    }
    cin >> a;
    cout << "Pop:\n";
    a = 1;
    while (a != 0)
    {
        cout << A.pop() << endl;
        A.print();
        cin >> a;
    }
    A.print();
    A.~Stack();
    return 0;
}

Stack::Stack()
{
    Size = 5;
    ArrayStack = new int[Size];
    top = 0;
}
Stack::~Stack()
{
    delete [] ArrayStack;
}
void Stack::print()
{
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    for (int i = 0; i < top; i++)
        cout << ArrayStack[i] << " ";
    cout << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}
void Stack::push(int value)
{
    if (top == Size)
        resize(Size * 2);
    ArrayStack[top] = value;
    top++;
}
void Stack::resize(int newSize)
{
    // int newSize = (int)(Size * 1.5);
    int *NewStack = new int [newSize];

    for (int i = 0; i < top; i++)
        NewStack[i] = ArrayStack[i];

    delete ArrayStack;
    Size = newSize;
    ArrayStack = NewStack;
}
int Stack::pop()
{
    if (top - 1 < 0)
    {
        cout << "Error: Stack is empty!" << endl;
        return 0;
    }
    if (top <= Size/2)
        resize((int)(Size/2));
    top--;
    return ArrayStack[top];
}