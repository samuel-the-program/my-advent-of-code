#include <iostream>
#include <fstream>
#include <vector>

struct PartNumber {
	int i;
	int j;
	int length;
	std::string num;
};

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

int main() {
	std::ifstream input{ "2023/inputs/day03-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::vector<std::string> engine{};
	std::string s;
	while (std::getline(input, s)) engine.push_back(s);
	
	std::vector<PartNumber> numbers{};
	for (int i = 0; i < engine.size(); ++i) {
		for (int j = 0; j < engine[i].size(); ++j) {
			if (isDigit(engine[i][j])) {
				PartNumber p{ i, j, 0 };
				p.num += engine[i][j];
				int length{ 1 };
				while (j + length < engine[i].size() && isDigit(engine[i][j+length])) {
					p.num += engine[i][j+length];
					++length;
				}
				p.length = length;
				numbers.push_back(p);
				
				j = j + length;
			}
		}
	}
	
	int sum = 0;
	for (PartNumber& p : numbers) {
		for (int i = p.i - 1; i <= p.i + 1; ++i) {
			for (int j = p.j - 1; j <= p.j + p.length; ++j) {
				if (i < 0 || j < 0 || i >= engine.size() || j >= engine[i].size()
					|| (i == p.i && j >= p.j && j < p.j + p.length)) continue;
				if (engine[i][j] != '.') {
					sum += std::stoi(p.num);
					break;
				}
			}
		}
	}
	
	std::cout << sum << '\n';
}