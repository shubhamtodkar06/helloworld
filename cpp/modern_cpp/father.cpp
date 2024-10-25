#include<iostream>
using namespace std;

class Father {
public:
    void print() { cout << "Father" << endl; }
};

class Son : protected Father { // Corrected inheritance specifier
public:
    Son() {Father::print();
            (new Father) -> print();
    }
};

int main() {
    Son t1;
    return 0;
}
