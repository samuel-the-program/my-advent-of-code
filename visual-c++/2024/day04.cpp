#include <iostream>
#include "../canva/canva.h"

int main() {
    clearScreen();
    moveCursor(4, 4);
    std::cout << "Offset";
}

// g++ ../canva/canva.cpp day04.cpp -o day04