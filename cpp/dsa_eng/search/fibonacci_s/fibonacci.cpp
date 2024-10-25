#include <iostream>
using namespace std;

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    int f1 = 0;
    int f2 = 1;
    int f3;


    while (f2 < 10)
    {
        int f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }

    int offset = -1;

    while(f3 > 1)
    {
        int i = min(offset+f1, 9);

        if(arr[i] < 8)
        {
            f3 = f2;
            f2 = f1;
            f1 = f3 - f1;
            offset = i;
        }

        else if(arr[i] > 8)
        {
            f3 = f1;
            f2 = f2 - f1;
            f1 = f3 - f2;
        }

        else
        {
            cout << "Found" << endl ;
            return 0;
        }
    }
    cout<<"Not Found" << endl;
}