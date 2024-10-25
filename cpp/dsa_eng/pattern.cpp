#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter a number : ";
    cin >> n;
    int i = 1;

    while(i <= n)
    {

        int bar = 1;
        while (bar < n -i +2)
        {
            cout << bar;

            bar ++;
        }

        // last second
        int foo = 0;
        while(foo < i -1)
        {
            cout<<'*' << '*';
            foo ++;
        }
        // last triangle
        int j = n -i +1;
        while (j > 0)
        {
            cout << j;
            j--;
        }
        cout << endl;
        i++;
    }

}
