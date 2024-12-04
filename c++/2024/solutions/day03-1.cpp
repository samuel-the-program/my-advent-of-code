#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int main() {
	std::ifstream input{ "../inputs/2024/day03-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    int total = 0;
    std::regex mulRegex("mul\\((\\d{1,3}),(\\d{1,3})\\)");
	while (std::getline(input, s)) {
        auto regexBegin = std::sregex_iterator(s.begin(), s.end(), mulRegex);
        auto regexEnd = std::sregex_iterator();
        for (std::sregex_iterator i = regexBegin; i != regexEnd; ++i) {
            std::smatch match = *i;
            total += std::stoi(match[1]) * std::stoi(match[2]);
        }
	}
    std::cout << total << '\n';
}