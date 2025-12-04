#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

std::string repeat(std::string s, int n) {
    std::string res = "";
    for (int i = 0; i < n; ++i) res += s;
    return res;
}

int main() {
	std::ifstream input{ "../inputs/2025/day02-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    input >> s;
    int comma = 0, nextComma = 0;
    long long total = 0;
	while (comma != s.npos) {
        if (comma == 0) comma = -1;
        nextComma = s.find(',', comma + 1);
        std::string range = s.substr(comma + 1, nextComma - comma - 1);
        std::string smin = range.substr(0, range.find('-'));
        std::string smax = range.substr(range.find('-') + 1);
        long long min = std::stoll(smin);
        long long max = std::stoll(smax);
        std::unordered_map<int, bool> invalidIDs{};

        for (int repeats = 2; repeats <= smax.size(); ++repeats) {
            std::string smax2 = smax;
            long long max2 = max;
            if (smax.size() % repeats != 0) {
                max2 = 1;
                for (int i = 0; i < (smax.size() / repeats) * repeats; ++i) max2 *= 10;
                max2 -= 1;
                smax2 = std::to_string(max2);
            }
            if (max2 < min) continue;

            std::string pattern = smax2.substr(0, smax2.size()/repeats);
            long long id = std::stoll(repeat(pattern, repeats));
            if (id > max) {
                pattern = std::to_string(std::stoll(pattern) - 1);
                id = std::stoll(repeat(pattern, repeats));
            }

            while (id >= min) {
                if (!invalidIDs[id]) {
                    total += id;
                    invalidIDs[id] = true;
                }
                pattern = std::to_string(std::stoll(pattern) - 1);
                id = std::stoll(repeat(pattern, repeats));
            }
        }
        
        comma = nextComma;
	}

    std::cout << total << '\n';
}