#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void PrintArray(int *Array, int Size)
{
    for (int j = 0; j < Size; j++) cout << Array[j] << " ";
    cout << endl;
}

void Swap(int &a, int &b)
{
    int prom = a;
    a = b;
    b = prom;
}

int Partition(int *Array, int Left, int Right)
{
    int pivot = Array[Left];
    int i = Left + 1;
    int j = Right;

    while (true)
    {
        while (i < Right && Array[i] < pivot)
            i++;

        while (Array[j] > pivot)
            j--;

        if (i >= j)
            break;
        
        Swap(Array[i++], Array[j--]);
    }

    Swap(Array[Left], Array[j]);
    return j;
}

void QuickSort(int *Array, int Left, int Right)
{
    if (Left >= Right)
        return;
    int pivotIndex = Partition(Array, Left, Right);
    QuickSort(Array, Left, pivotIndex - 1);
    QuickSort(Array, pivotIndex + 1, Right);
}

int main()
{
    srand(time(NULL));

    int *Array, Size;
    Size = 30000000;
    Array = new int [Size];
    for (int i = 0; i < Size; i++)
    {
        Array[i] = rand() % 30000001 - 15000000;
        //cout << Array[i] << " ";
    }
    cout << endl;
    QuickSort(Array, 0, Size - 1);
    PrintArray(Array, Size);

    return 0;
}
