#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

bool safeDiffs(std::vector<int>& diffs) {
    int prevN = -1;
    bool first = true;
    for (const int& n : diffs) {
        if (std::abs(n) < 1 || std::abs(n) > 3) {
            return false;
        }
        if (!first) {
            if ((prevN > 0) != (n > 0)) {
                return false;
            }
        }
        first = false;
        prevN = n;
    }
    return true;
}

int main() {
	std::ifstream input{ "../inputs/2024/day02-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    int numSafe = 0;
	while (std::getline(input, s)) {
        int num = 0;
        int prevNum = -1;
        int idx = 0;
        int nextIdx = 0;
        std::vector<int> diffs{};
        while (nextIdx != s.npos) {
            nextIdx = s.find(" ", idx);
            num = std::stoi(s.substr(idx, nextIdx-idx));
            if (prevNum != -1) diffs.push_back(num - prevNum);
            idx = nextIdx + 1;
            prevNum = num;
        }
        /*for (int n : diffs) {
            std::cout << n << ' ';
        }
        std::cout << '\n';*/
        if (safeDiffs(diffs)) ++numSafe;

    }
    std::cout << numSafe << '\n';
}