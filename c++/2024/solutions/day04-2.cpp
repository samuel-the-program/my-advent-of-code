#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2024/day04-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::vector<std::string> grid{};
    std::string s;
	while (std::getline(input, s)) {
        grid.push_back(s);
    }

    int count = 0;
    for (int i = 0; i < grid.size() - 2; ++i) {
    for (int j = 0; j < grid[i].size() - 2; ++j) {
        if (grid[i+1][j+1] != 'A') continue;
        std::vector<char> corners{grid[i][j], grid[i][j+2], grid[i+2][j], grid[i+2][j+2]};
        bool forwardDiag = (corners[0] == 'M' && corners[3] == 'S') + (corners[0] == 'S' && corners[3] == 'M');
        bool backwardDiag = (corners[1] == 'M' && corners[2] == 'S') + (corners[1] == 'S' && corners[2] == 'M');
        if (forwardDiag && backwardDiag) {
            ++count;
        }
    }
    }
    std::cout << count << '\n';
}