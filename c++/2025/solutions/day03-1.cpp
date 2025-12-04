#include <iostream>
#include <string>
#include <fstream>

int main() {
	std::ifstream input{ "../inputs/2025/day03-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    int totalJolt = 0;
	while (std::getline(input, s)) {
        char first = s[0];
        char second = '0';
        for (int i = 1; i < s.size() - 1; ++i) {
            if (s[i] > first) {
                first = s[i];
                second = ' ';
            } else if (s[i] > second) {
                second = s[i];
            }
        }
        if (s[s.size() - 1] > second) second = s[s.size() - 1];
        int maxJolt = (first - '0') * 10 + (second - '0');
        totalJolt += maxJolt;
	}

    std::cout << totalJolt << '\n';
}