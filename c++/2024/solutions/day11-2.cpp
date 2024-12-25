#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

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

    std::map<long long, long long> stones{};
    for (long long stone : list) {
        ++stones[stone];
    }

    for (int i = 0; i < 75; ++i) {
        std::map<long long, long long> adds{};
        for (const auto& count : stones) {
            const long long& stoneNum = count.first;
            const long long& amount = count.second;
            std::string stoneStr = std::to_string(stoneNum);

            adds[stoneNum] -= amount;
            if (stoneNum == 0) {
                adds[1] += amount;
            } else if (stoneStr.size() % 2 == 0) {
                adds[std::stoll(stoneStr.substr(0, stoneStr.size() / 2))] += amount;
                adds[std::stoll(stoneStr.substr(stoneStr.size() / 2))] += amount;
            } else {
                adds[stoneNum * 2024] += amount;
            }
        }
        for (const auto& count : adds) {
            stones[count.first] += count.second;
        }
    }

    long long numRocks = 0;
    for (const auto& count : stones) {
        numRocks += count.second;
    }

    std::cout << numRocks << '\n';
}