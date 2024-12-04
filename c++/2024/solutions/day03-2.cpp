#include <iostream>
#include <string>
#include <fstream>
#include <regex>

int main() {
	std::ifstream input{ "../inputs/2024/day03-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    int total = 0;
    std::regex mulRegex("(?:(mul)\\((\\d{1,3}),(\\d{1,3})\\))|(do)\\(\\)|(don't)\\(\\)");
    bool enabled = true;
	while (std::getline(input, s)) {
        auto regexBegin = std::sregex_iterator(s.begin(), s.end(), mulRegex);
        auto regexEnd = std::sregex_iterator();
        for (std::sregex_iterator i = regexBegin; i != regexEnd; ++i) {
            std::smatch match = *i;
            if (match[4] == "do") {
                enabled = true;
            } else if (match[5] == "don't") {
                enabled = false;
            }
            
            if (match[1] == "mul" && enabled) total += std::stoi(match[2]) * std::stoi(match[3]);
        }
	}
    std::cout << total << '\n';
}