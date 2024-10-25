#include<iostream>
using namespace std;

class ClassA {
protected:
    int b;
public:
    ClassA(int i) : b(i) {}
    virtual void f(ClassA *t) { cout << t->b << "Base"<< endl; }
};

class ClassB : public ClassA {
    int d;
public:
    ClassB(int i = 0, int j = 0) : ClassA(i), d(j) {}
    void f(ClassB *t) { cout << t->d << "derived" << endl; }
};

int main() {
    ClassA *t1 = new ClassB(1, 2);
    t1->f(new ClassB); // Line-1
    return 0;
}
