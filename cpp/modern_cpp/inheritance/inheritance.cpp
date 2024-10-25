#include <iostream>
using namespace std;

class Base {
protected:
    double i;
public:
    Base(double _i) : i(_i) {}
    void calculate() { cout << i << endl; }
};

class Derived: public Base {
public:
    Derived(double _i) : Base(_i) {}

    void calculate(){Base::calculate();}

    // Overloaded calculate() method with a different parameter list
    void calculate(double pi) { cout << i * pi << endl; }
};

int main() {
    Derived d(6.75);
    d.calculate(3.14); // Calls the overloaded calculate() method in Derived
    d.calculate(); // Calls the calculate() method inherited from Base
    return 0;
}
