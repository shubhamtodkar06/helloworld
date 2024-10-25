#include <iostream>
using namespace std;

class Base{
    public:
         virtual void fun(){ cout << "base"; }
};

class Derived : public Base{
    public:
         void fun(double i){ cout << "derived"; }
};

int main(){
    Derived t1;
    Base *t2 = new Derived();
    //t1.fun();
    //t1.fun(1.23);
    //t2 -> fun(12.23);
    //t2 -> fun();
    return 0;

}
