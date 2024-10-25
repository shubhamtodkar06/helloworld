#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Size of an Array : ";
    cin >> size;

    int arr[size + 1];
    for (int i=0; i<size; i++)
    {
        int bar;
        cout << "Enter a Number : ";
        cin >> bar;
        arr[i] = bar;
    }

    cout << "Enter a Number to Insert : ";
    int inser;
    cin >> inser;
    cout << "Enter a Position to Insert in Arrry(Less than " << size << ") : ";
    int pos;
    cin >> pos;



    for (int i=size -1; i >= pos-1; i--)
    {
        arr[i+1] = arr[i];
    }
    arr[pos-1] = inser;

    for (int i=0; i<= size; i++)
    {
        cout<<arr[i]<<endl;
    }
    return 0;
}