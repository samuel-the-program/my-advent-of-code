#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

int main() {
	std::ifstream input{ "2023/inputs/day02-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::string s;
	std::regex r{"(\\d+) (\\w+)"};
	
	int result = 0;
	int curGame = 1;
	while (std::getline(input, s)) {
		auto start = s.find(":") + 2;
		std::smatch m;
		int red = 0;
		int green = 0;
		int blue = 0;
		while (std::regex_search(s, m, r)) {
			int num = std::stoi(m[1]);
			std::string color = m[2];
			
			if (color == "red" && num > red) {
				red = num;
			} else if (color == "green" && num > green) {
				green = num;
			} else if (color == "blue" && num > blue) {
				blue = num;
			}
			s = m.suffix();
		}
		int power = red * green * blue;
		result += power;
	}
	std::cout << result << '\n';
}