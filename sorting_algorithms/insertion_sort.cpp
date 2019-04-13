#include <iostream>

using namespace std;

void insertion_sort(int *Array, int start, int end)
{
	int n;
	for (int i = start + 1; i < end; i++)
	{
		n = i;
		while (n >= start + 1 && Array[n] < Array[n - 1])
		{
			swap(Array[n], Array[n - 1]);
			n--;
		}
	}
}

int main()
{
	
	return 0;
}