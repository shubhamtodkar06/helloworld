#include <iostream>
using namespace std;

int main()
{
    int arr[10] = {34,54,65,45,34,464,4654,345,34546,4565};
    bool check = true;
    while(check)
    {
        check = false;
        for (int i = 0; i < 9; i ++)
        {
            if (arr[i] > arr[i+1])
            {
                swap(arr[i], arr[i+1]);
                check = true;
            }
        }
    }
    for (int i = 0; i < 10; i ++)
    {
        cout<<arr[i]<<endl;
    }


}