#include <iostream>
#include "point.h"

int main() {
    Point test1{{2, 3, 4, 5, 6}};
    Point test2{{2, 3, 4, 5, 6}};
    std::cout<< (test1 + test2)[2];
}