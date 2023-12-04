#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

int main() {
	std::ifstream input{ "../inputs/2023/day02-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::string s;
	std::regex r{"(\\d+) (\\w+)"};
	
	int result = 0;
	int curGame = 1;
	while (std::getline(input, s)) {
		auto start = s.find(":") + 2;
		std::smatch m;
		bool valid = true;
		while (std::regex_search(s, m, r)) {
			int num = std::stoi(m[1]);
			std::string color = m[2];
			
			if (color == "red" && num > 12) {
				valid = false;
				break;
			} else if (color == "green" && num > 13) {
				valid = false;
				break;
			} else if (color == "blue" && num > 14) {
				valid = false;
				break;
			}
			s = m.suffix();
		}
		if (valid) 
			result += curGame;
		++curGame;
	}
	std::cout << result << '\n';
}