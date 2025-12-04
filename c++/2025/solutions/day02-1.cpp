#include <iostream>
#include <string>
#include <fstream>

int main() {
	std::ifstream input{ "../inputs/2025/day02-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    input >> s;
    int comma = -1, nextComma = 0;
    long long total = 0;
	while ((nextComma = s.find(',', comma + 1)) != s.npos) {
        std::string range = s.substr(comma + 1, nextComma - comma - 1);
        std::string smin = range.substr(0, range.find('-'));
        std::string smax = range.substr(range.find('-') + 1);
        long long min = std::stoll(smin);
        long long max = std::stoll(smax);

        if (smax.size() % 2 == 1) {
            max = 1;
            for (int i = 0; i < smax.size() - 1; ++i) max *= 10;
            max -= 1;
            smax = std::to_string(max);
        }

        std::string pattern = smax.substr(0, smax.size()/2);
        long long id = std::stoll(pattern + pattern);
        if (id > max) {
            pattern = std::to_string(std::stoll(pattern) - 1);
            id = std::stoll(pattern + pattern);
        }

        while (id >= min) {
            total += id;
            pattern = std::to_string(std::stoll(pattern) - 1);
            id = std::stoll(pattern + pattern);
        }
        comma = nextComma;
	}

    std::cout << total << '\n';
}