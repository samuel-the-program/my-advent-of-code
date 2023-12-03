#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
	std::ifstream input{ "2023/inputs/day01-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	std::regex r{ "one|two|three|four|five|six|seven|eight|nine|\\d"};
	std::vector<std::string> numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	std::string s;
	int sum{};
	while (std::getline(input, s)) {
		std::string num;
		std::smatch m{};
		std::regex_search(s, m, r);
		std::string first = m[0];
		std::string last;
		while (std::regex_search(s, m, r)) {
			last = m[0];
			s = s.substr(1);
		}
		int f, l;
		if (first.size() > 1) {
			f = std::distance(numbers.begin(), std::find(numbers.begin(), numbers.end(), first)) + 1;
		} else {
			f = first[0] - '0';
		}
		if (last.size() > 1) {
			l = std::distance(numbers.begin(), std::find(numbers.begin(), numbers.end(), last)) + 1;
		} else {
			l = last[0] - '0';
		}
		sum += f*10 + l;
	}
	std::cout << sum << '\n';
}