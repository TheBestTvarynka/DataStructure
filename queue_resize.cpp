#include <iostream>

using namespace std;

class queue
{
    int *array;
    int size, top, bottom;
    // top - pointer to position where will be next element
public:
    queue();
    ~queue();
    void print();
    void push(int );
    void resize(int );
    int pop();
};

queue::queue()
{
    size = 5;
    array = new int[size];
    bottom = 0;
    top = 0;
}
queue::~queue()
{
    delete [] array;
}
void queue::print()
{
    int f, s;
    if (top < bottom)
    {
        f = size;
        s = top;
    }
    else
    {
        s = 0;
        f = top;
    }
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    for (int i = bottom; i < f; i++)
        cout << array[i] << " ";
    for (int j = 0; j < s; j++)
        cout << array[j] << " ";
    cout << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}
void queue::resize(int new_size)
{
    int *new_array = new int[new_size];
    int s, f, p;
    if (top <= bottom)
    {
        f = size;
        s = top;
    }
    else
    {
        s = 0;
        f = top;
    }
    for (int i = bottom; i < f; i++)
        new_array[i - bottom] = array[i];
    p = f - bottom;
    for (int j = 0; j < s; j++)
        new_array[p + j] = array[j];
    bottom = 0;
    top = p + s;
    size = new_size;
    delete array;
    array = new_array;
}
int queue::pop()
{
    int result, s = size;
    if (top == bottom)
    {
        cout << "Error: Queue is empty" << endl;
        return 0;
    }
    result = array[bottom];
    bottom++;
    // if bottom will be equal 0 it's mean that queue is empty
    if (top < bottom)
        s = size - bottom + size;
    if (top > bottom)
        s = top - bottom;
    if (s <= size/4)
        resize(size/2);
    return result;
}
void queue::push(int item)
{
    array[top] = item;
    top++;
    if (top == bottom)
        resize(size*2);
    if (top == size)
    {
        if (bottom > 0)
            top = 0;
        else
            resize(size * 2);
    }
}

int main()
{
    queue A;
    A.push(6);
    A.push(7);
    A.push(8);
    A.push(9);
    A.push(0);
    A.push(10);
    A.push(11);
    A.push(12);
    A.print();
    A.pop();
    A.pop();
    A.pop();
    A.pop();
    A.pop();
    A.print();
    A.push(1);
    A.push(2);
    A.push(3);
    A.push(4);
    A.push(5);
    A.print();
    A.~queue();
    return  0;
}