#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../../aoc-utils/aoc-utils.h"

int main() {
	std::ifstream input{ "../inputs/2023/day04-input.txt" };
	std::vector<int> winCounts{};
	
	std::string s;
	int gameNum = 1;
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
		
		int matches = 0;
		for (int n : winNums) {
			if (std::find(holdNums.begin(), holdNums.end(), n) != holdNums.end()) ++matches;
		}
		
		winCounts.push_back(matches);
		++gameNum;
	}
	
	std::vector<int> cards(winCounts.size(), 1);
	for (int i = 0; i < cards.size(); ++i) {
		int upTo = winCounts[i] + i > cards.size() - 1 ? cards.size() - 1 : winCounts[i] + i;
		for (int j = i + 1; j <= upTo; ++j) cards[j] += cards[i];
	}
	
	std::cout << cards << '\n';
	
	int sum = 0;
	for (int c : cards) {
		sum += c;
	}
	std::cout << sum << '\n';
}