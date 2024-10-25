#include <iostream>
using namespace std;

int search(int arr[], int n, int key)
{
    if (n==0)
        return -1;

    if (arr[0] == key)
        return 1;
    else
        return search(arr+1, n-1, key);
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 1;
    int num = search(arr, 10, key);
    if (num == 1)
        cout << "found" << endl;
    else
        cout << "Not Found" << endl;
}