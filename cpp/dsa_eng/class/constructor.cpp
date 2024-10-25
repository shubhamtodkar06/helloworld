#include <iostream>
using namespace std;

class fruit
{
    public:
    string name, colour;
    int quantity;


    fruit(string x, string y, int z)
    {
        name = x;
        colour = y;
        quantity = z;
    }

};

int main()
{
    fruit apple("apple", "red", 10);
    fruit banana("banana", "yellow", 12);
    cout << apple.name<< " " << apple.colour<<endl;
}