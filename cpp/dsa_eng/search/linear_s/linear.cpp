#include <iostream>
using namespace std;

int main()
{
    int arr[] = {1, 3, 4, 5, 45, 435, 34, 23, 223, 432, 3, 6, 9};
    int num = 9;
    for (int i=0; i<=12; i++)
    {
        if (arr[i] == num)
        {
            cout << "found" << endl;
            return 0;
        }
    }
    cout << "Not found" << endl;
}
