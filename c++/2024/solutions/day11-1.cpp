#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
	std::ifstream input{ "../inputs/2024/day11-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
	std::getline(input, s);
    size_t pos_start = 0, pos_end;
    std::string token;
    std::vector<long long> list;
    while ((pos_end = s.find(' ', pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        list.push_back(std::stoll(token));
    }
    list.push_back(std::stoll(s.substr(pos_start)));

    int numRocks = 0;
    for (int startRock : list) {
        std::vector<long long> rocks{startRock};
        for (int blinks = 0; blinks < 25; ++blinks) {
            int size = rocks.size();
            for (int i = 0; i < size; ++i) {
                long long& curRock = rocks[i];
                std::string rockStr = std::to_string(curRock);
                if (curRock == 0) {
                    curRock = 1;
                } else if (rockStr.size() % 2 == 0) {
                    curRock = std::stoi(rockStr.substr(0, rockStr.size() / 2));
                    rocks.push_back(std::stoi(rockStr.substr(rockStr.size() / 2)));
                } else {
                    curRock *= 2024;
                }
            }
        }
        numRocks += rocks.size();
    }

    std::cout << numRocks << '\n';
}