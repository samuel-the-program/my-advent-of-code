#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
	std::ifstream input{ "../inputs/2024/day01-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    std::vector<int> first{};
    std::map<int, int> second{};
	while (std::getline(input, s)) {
		std::string fir = s.substr(0, s.find_first_of(" "));
        std::string sec = s.substr(s.find_last_of(" ") + 1);
        first.push_back(std::stoi(fir));
        second[std::stoi(sec)] += 1;
	}

    int similarity = 0;
    for (int i = 0; i < first.size(); ++i) {
        similarity += first[i] * second[first[i]];
    }
    std::cout << similarity << '\n';
}