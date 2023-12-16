#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2023/day09-input.txt" };
	
	std::string line;
	int res = 0;
	while (std::getline(input, line)) {
		std::vector<std::vector<int>> diffTable{};
		diffTable.push_back(std::vector<int>{});
		int pos = line.find(' ');
		int lastPos = 0;
		
		while (pos != line.npos) {
			diffTable[0].push_back( std::stoi(line.substr(lastPos, pos)) );
			lastPos = pos + 1;
			pos = line.find(' ', lastPos);
		}
		diffTable[0].push_back(std::stoi(line.substr(lastPos)));
		
		while (!std::all_of(diffTable.back().begin(), diffTable.back().end(),
		 [](int x){ return x == 0; })) {
			diffTable.push_back(std::vector<int>{});
			std::vector<int>& sequence = diffTable[diffTable.size()-2];
			std::vector<int>& diff = diffTable.back();
			for (int i = 0; i < sequence.size()-1; ++i) {
				diff.push_back(sequence[i+1] - sequence[i]);
			}
		}
		
		for (int i = diffTable.size()-1; i > 0; --i) {
			diffTable[i-1].insert(diffTable[i-1].begin(),
				diffTable[i-1][0] - diffTable[i][0]);
		}
		
		res += diffTable[0][0];
	}
	
	std::cout << res << '\n';
}