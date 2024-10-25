#include <iostream>
using namespace std;

int main()
{
    int arr[10];
    for (int i=0; i<10; i++)
    {
        std::cout << "Enter a Number : ";
        std::cin >> arr[i];
    }

    for (int j=0; j<10; j++)
    {
        std::cout<<"Element[" << j+1 << "] : " << arr[j] << endl;
    }
}