#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

bool canReact(char c1, char c2) {
	return (c1 >= 'a' && c1 <= 'z' && c2 == c1 - 32) ||
	       (c1 >= 'A' && c1 <= 'Z' && c2 == c1 + 32);
}

int reactionSize(std::string& s) {
	bool finished{ false };
	while (!finished) {
		finished = true;
		for (int i{ 0 }; i < s.size() - 1; ++i) {
			if (canReact(s[i], s[i+1])) {
				finished = false;
				s.erase(i, 2);
				continue;
			}
		}
	}
	return s.size();
}

int main() {
	std::ifstream input{ "inputs/day05-input.txt" };
	if (!input.is_open()) std::cout << "failed to open file\n";
	std::string polymer{};
	input >> polymer;
	
	int minSize{ static_cast<int>(polymer.size()) };
	for (char type{ 'A' }; type <= 'Z'; ++type) {
		std::string curPoly{ polymer };
		auto it = std::remove(curPoly.begin(), curPoly.end(), type);
		curPoly.erase(it, curPoly.end());
		it = std::remove(curPoly.begin(), curPoly.end(), type + 32);
		curPoly.erase(it, curPoly.end());
		int reactSize{ reactionSize(curPoly) };
		if (reactSize < minSize) minSize = reactSize;
	}
	
	std::cout << minSize << '\n';
}