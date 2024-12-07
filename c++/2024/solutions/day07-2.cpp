#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
	std::ifstream input{ "../inputs/2024/day07-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    unsigned long long totalCal = 0;
	while (std::getline(input, s)) {
        int listPos = s.find(':');
        unsigned long long target = std::stoull(s.substr(0, listPos));
        std::string listStr = s.substr(listPos + 2);

        size_t pos_start = 0, pos_end;
		std::string token;
		std::vector<unsigned long long> list;

		while ((pos_end = listStr.find(' ', pos_start)) != std::string::npos) {
			token = listStr.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + 1;
			list.push_back(std::stoull(token));
		}
		list.push_back(std::stoull(listStr.substr(pos_start)));

        std::vector<char> ops(list.size() - 1, '|');
        for (int n = 0; n < std::pow(3, ops.size()); ++n) {
            unsigned long long res = list[0];
            for (int i = 0; i < ops.size(); ++i) {
                if (ops[i] == '|') {
                    /*std::string newRes = std::to_string(res) + std::to_string(list[i+1]);
                    res = std::stoull(newRes);
                    */
                    res *= std::round(std::pow(10, std::ceil(std::log10(list[i+1] + 1))));
                    res += list[i + 1];
                } else if (ops[i] == '*') {
                    res *= list[i+1];
                } else if (ops[i] == '+') {
                    res += list[i+1];
                }
                if (res > target) break;
            }
            if (res == target) {
                totalCal += target;
                break;
            }

            int j = ops.size() - 1;
            while (j >= 0 && ops[j] == '+') {
                ops[j] = '|';
                --j;
            }
            if (j >= 0) {
                if (ops[j] == '|') {
                    ops[j] = '*';
                } else if (ops[j] == '*') {
                    ops[j] = '+';
                }
            }
        }
	}
    std::cout << totalCal << '\n';
}