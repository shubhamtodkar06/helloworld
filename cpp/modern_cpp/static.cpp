#include<iostream>
using namespace std;
class myClass{
    char c;
    static myClass *obj;                   //LINE-1
    myClass(char x) : c(x) { }
    public:
        static myClass* create(char x){    //LINE-2
            if(!obj)
                obj = new myClass(x);
            return obj;
        }
        void show();
};
myClass* myClass::obj =nullptr;//LINE-3
void myClass::show(){
    cout << c;
}
int main(){
    int x, y;
    myClass *s1, *s2;
    cin >> x >> y;
    s1 = myClass::create(x);
    s2 = myClass::create(y);
    s1->show();
    s2->show();
    return 0;
}
