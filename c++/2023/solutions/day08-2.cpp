#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <numeric>

using StringPair = std::pair<std::string, std::string>;

int main() {
	std::ifstream input{ "../inputs/2023/day08-input.txt" };
	std::string dirs;
	std::getline(input, dirs);
	
	std::vector<std::string> starts{};
	std::map<std::string, StringPair> map{};
	std::string line;
	std::getline(input, line);
	while (std::getline(input, line)) {
		std::string start = line.substr(0, 3);
		std::string left = line.substr(7, 3);
		std::string right = line.substr(12, 3);
		if (start[2] == 'A') starts.push_back(start);
		map[start] = StringPair{left, right};
	}
	
	auto isEnd = [](std::string& s){ return s[2] == 'Z'; };
	
	std::vector<int> lengths{};
	
	for (std::string curNode : starts) {
		int dirI = 0;
		int length = 0;
		while (curNode[2] != 'Z') {
			if (dirs[dirI] == 'L') {
				curNode = map[curNode].first;
			} else {
				curNode = map[curNode].second;
			}
			++dirI;
			dirI %= dirs.size();
			++length;
		}
		lengths.push_back(length);
	}
	
	long long res = std::lcm(lengths[0], lengths[1]);
	for (int i = 2; i < lengths.size(); ++i) {
		res = std::lcm(res, lengths[i]);
	}
	std::cout << res << '\n';
}