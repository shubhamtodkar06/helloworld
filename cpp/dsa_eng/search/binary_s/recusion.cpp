#include <iostream>
using namespace std;

int binary(int arr[], int key, int size)
{
    int first = 0;
    int last = size -1;
    if (size == 0)
    {
        return -1;
    }

    int mid = (first + last) /2;

    if (arr[mid] == key)
    {
        return 1;
    }
    else
    {
        if (arr[mid] > key)
        {
            binary(arr, key, mid -1);
        }
        else
        {
            binary(arr+mid+1, key, size - mid + 1);
        }
    }
    return -1;
}


int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int num = binary(arr, 50, 10);
    if (num == 1)
    {
        cout << "Found" << endl;
    }
    else if(num == -1)
    {
        cout << "Not Found" << endl;
    }
}