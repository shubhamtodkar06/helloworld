#include <iostream>
using namespace std;

int search(int arr[], int size, int key)
{
    int first = 0;
    int last = size - 1;
    while(first <= last)
    {
        int mid = (first+last) / 2;
        if (arr[mid] == key)
        {
            return 1;
        }
        else
        {
            if (key > arr[mid])
            {
                first = mid + 1;
            }
            else
            {
                last = mid - 1;
            }
        }
    }
    return -1;
}

int main()
{
    int arr[5] = {1, 2, 3, 4,5};
    int num = search(arr, 323, 3);

    if (num == 1)
    {
        cout << "Found" << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }
}