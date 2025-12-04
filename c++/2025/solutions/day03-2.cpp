#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2025/day03-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";

    std::string s;
    long long totalJolt = 0;
	while (std::getline(input, s)) {
        std::vector<char> jolt(12, '0');

        for (int i = 0; i < s.size(); ++i) {
            int minJ = std::max(0, (int) (i - s.size() + jolt.size()));
            for (int j = minJ; j < jolt.size(); ++j) {
                if (s[i] > jolt[j]) {
                    jolt[j] = s[i];
                    for (int k = j + 1; k < jolt.size(); ++k) jolt[k] = '0';
                    break;
                }
            }
        }
        long long numJolt = 0;
        for (int i = 0; i < jolt.size(); ++i) {
            numJolt *= 10;
            numJolt += jolt[i] - '0';
        }
        totalJolt += numJolt;
	}

    std::cout << totalJolt << '\n';
}