#include "point.h"
#include <iostream>

double LeakTest() {
    double* leak = new double[30];
    for (int i = 1; i < 20; ++i) {
        leak[i] = i + 8;
    }
    return leak[6];
}

int main() {
    Point memoryLeak(5);
    std::cout << LeakTest();
    return 0;
}