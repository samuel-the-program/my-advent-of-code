#include <string>
#include <iostream>

namespace Code {
    const std::string ESC = "\x1b";
}

enum class Color {
    fBlack = 30,
    fRed,
    fGreen,
    fYellow,
    fBlue,
    fMagenta,
    fCyan,
    fWhite,
    bBlack = 40,
    bRed,
    bGreen,
    bYellow,
    bBlue,
    bMagenta,
    bCyan,
    bWhite
};

void clearScreen() {
    std::cout << Code::ESC << "[2J";
}

void moveCursor(int x, int y) {
    std::cout << Code::ESC << '[' << std::to_string(x) << ';' << std::to_string(y) << 'H';
}

void setColor(Color c) {
    std::cout << Code::ESC << '[' << static_cast<int>(c) << 'm';
}

void resetStyle() {
    std::cout << Code::ESC << "[0m";
}

int main() {
    clearScreen();
    moveCursor(2, 2);
    setColor(Color::bCyan);
    std::cout << "Offset";

    resetStyle();
}