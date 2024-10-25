#include <iostream>
using namespace std;

int main()
{
    int arr[10] = {34,54,65,45,466522,464,4654,345,34546,4565};

    for (int i=0; i<9; i++)
    {
        if (arr[i]>arr[i+1])
        {
            int temp = arr[i+1];
            int j = i;
            while(j>=0 && temp < arr[j])
            {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] =temp;
        }
    }

    for (int i = 0; i < 10; i ++)
    {
        cout<<arr[i]<<endl;
    }
}