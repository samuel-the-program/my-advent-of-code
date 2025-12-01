#include <iostream>
#include <string>
#include <fstream>

int main() {
	std::ifstream input{ "../inputs/2025/day01-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    int dial = 50;
    int password = 0;
	while (std::getline(input, s)) {
        bool dir = s[0] == 'R' ? true : false;
        int distance = std::stoi(s.substr(1));
        dial += distance * (dir ? 1 : -1);
        if (dial < 0) {
            while (dial < 0) dial += 100;
        } else if (dial >= 100) {
            while (dial >= 100) dial -= 100;
        }
        if (dial == 0) {
            ++password;
        }
	}

    std::cout << password << '\n';
}