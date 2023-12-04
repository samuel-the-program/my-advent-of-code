#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2023/day04-input.txt" };
	
	std::string s;
	int sum = 0;
	while (std::getline(input, s)) {
		std::vector<int> winNums{};
		std::vector<int> holdNums{};
		
		auto splitPos = s.find("|");
		for (int i = 10; i < splitPos; i += 3) {
			winNums.push_back(std::stoi(s.substr(i, i+3)));
		}
		for (int i = splitPos + 2; i < s.size(); i += 3) {
			holdNums.push_back(std::stoi(s.substr(i, i+3)));
		}
		
		int points = 0;
		for (int n : winNums) {
			if (std::find(holdNums.begin(), holdNums.end(), n) != holdNums.end()) {
				if (points == 0) {
					points = 1;
				} else {
					points *= 2;
				}
			}
		}
		sum += points;
	}
	
	std::cout << sum << '\n';
}