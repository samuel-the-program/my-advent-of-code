#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

bool letterAmount(std::string_view s, int amt) {
	std::unordered_map<char, int> counts{};
	counts.reserve(26);
	
	for (char c : s) {
		++counts[c];
	}
	
	for (auto pair : counts) {
		if (pair.second == amt) return true;
	}
	return false;
}

int main() {
	std::ifstream input{"inputs/day02-input.txt"};
	if (!input.is_open()) std::cout << "file not open\n";
	
	std::string s{};
	int twoLetters{};
	int threeLetters{};
	while (std::getline(input, s)) {
		if (letterAmount(s, 2)) ++twoLetters;
		if (letterAmount(s, 3)) ++threeLetters;
	}
	
	std::cout << twoLetters * threeLetters << '\n';
}