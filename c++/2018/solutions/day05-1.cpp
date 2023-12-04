#include <iostream>
#include <fstream>
#include <string>

bool canReact(char c1, char c2) {
	return (c1 >= 'a' && c1 <= 'z' && c2 == c1 - 32) ||
	       (c1 >= 'A' && c1 <= 'Z' && c2 == c1 + 32);
}

int main() {
	std::ifstream input{ "../inputs/2018/day05-input.txt" };
	if (!input.is_open()) std::cout << "failed to open file\n";
	std::string polymer{};
	input >> polymer;
	
	bool finished{ false };
	while (!finished) {
		finished = true;
		for (int i{ 0 }; i < polymer.size() - 1; ++i) {
			if (canReact(polymer[i], polymer[i+1])) {
				finished = false;
				polymer.erase(i, 2);
				continue;
			}
		}
	}
	std::cout << polymer.size() << '\n';
}