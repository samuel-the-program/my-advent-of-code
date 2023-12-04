#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

int main() {
	std::ifstream input{ "../inputs/2023/day01-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::string s;
	int sum{};
	while (std::getline(input, s)) {
		std::string num;
		char first = '/';
		char last = '/';
		for (char c : s) {
			if (std::isdigit(c)) {
				last = c;
				if (first == '/') first = c;
			}
		}
		int n = (first-'0') * 10 + (last-'0');
		sum += n;
	}
	std::cout << sum << '\n';
}