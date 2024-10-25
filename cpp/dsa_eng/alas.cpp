#include <iostream>

using namespace std;

void compute(int x1, int x2, int x3, int& x4) {
    x3 = x1 + x2; // Calculate sum and assign to x3 by reference
    x4 = x1 * x3; // Calculate product and assign to x4 by reference
}

int main() {
    int a = 10, b = 20, c = 1, d = 1;
    compute(a, b, c, d); // Pass c as a reference and calculate d
    cout << c << ", "; // Print value of c
    cout << d; // Print value of d
    return 0;
}
