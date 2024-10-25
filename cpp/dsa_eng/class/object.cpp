#include <iostream>
using namespace std;

class world
{
    public:
        int funtion();
};

int world::funtion()
{
    int a, b;
    do
    {
        cout << "Enter a First Number : ";
        cin >> a;
        cout << "Enter a Second Number : ";
        cin >> b;
    }while(a<=0 || a>=100 || b<=0 || b>=100);
    return (a + b);

}


int main()
{
    world object;
    int c = object.funtion();

    std::cout << "Sum of Both Numbers : " << c << endl;
    return 0;
}