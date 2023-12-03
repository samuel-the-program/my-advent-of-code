#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct PartNumber {
	int i{};
	int j{};
	int length{};
	std::string num{};
};

struct Gear {
	int i{};
	int j{};
	std::vector<PartNumber> adjs{};
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
	std::vector<Gear> gears{};
	for (int i = 0; i < engine.size(); ++i) {
		for (int j = 0; j < engine[i].size(); ++j) {
			if (engine[i][j] == '*') {
				gears.push_back(Gear{i, j});
			} else if (isDigit(engine[i][j])) {
				PartNumber p{ i, j, 0 };
				p.num += engine[i][j];
				int length{ 1 };
				while (j + length < engine[i].size() && isDigit(engine[i][j+length])) {
					p.num += engine[i][j+length];
					++length;
				}
				p.length = length;
				numbers.push_back(p);
				
				j = j + length - 1;
			}
		}
	}
	
	for (PartNumber& p : numbers) {
		for (int i = p.i - 1; i <= p.i + 1; ++i) {
			for (int j = p.j - 1; j <= p.j + p.length; ++j) {
				if (i < 0 || j < 0 || i >= engine.size() || j >= engine[i].size()
					|| (i == p.i && j >= p.j && j < p.j + p.length)) continue;
				if (engine[i][j] == '*') {
					auto it = std::find_if(gears.begin(), gears.end(), 
						[i, j](Gear& g){ return g.i == i && g.j == j; });
					(it->adjs).push_back(p);
				}
			}
		}
	}
	
	int sum = 0;
	for (Gear& g : gears) {
		if (g.adjs.size() == 2) {
			sum += std::stoi(g.adjs[0].num) * std::stoi(g.adjs[1].num);
		}
	}
	
	std::cout << sum << '\n';
}