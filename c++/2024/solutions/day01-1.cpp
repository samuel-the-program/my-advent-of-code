#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2024/day01-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    std::vector<int> first{};
    std::vector<int> second{};
	while (std::getline(input, s)) {
		std::string fir = s.substr(0, s.find_first_of(" "));
        std::string sec = s.substr(s.find_last_of(" ") + 1);
        first.push_back(std::stoi(fir));
        second.push_back(std::stoi(sec));
	}
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    int total = 0;
    for (int i = 0; i < first.size(); ++i) {
        int diff = first[i] - second[i];
        if (diff < 0) diff *= -1;
        total += diff;
    }
    std::cout << total << '\n';
}