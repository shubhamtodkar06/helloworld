#include <iostream>
#include <vector>
using namespace std;

int main(void){
    cout << "Enter Size of an Array : ";
    int size;
    cin >> size;

    vector<int> array;
    array.resize(size);

    for (int i = 0; i < size; i++){
        array[i] = i + 1;
    }
    for (int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}
