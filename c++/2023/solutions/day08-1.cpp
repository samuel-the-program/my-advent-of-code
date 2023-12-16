#include <iostream>
#include <fstream>
#include <map>
#include <utility>

using StringPair = std::pair<std::string, std::string>;

int main() {
	std::ifstream input{ "../inputs/2023/day08-input.txt" };
	std::string dirs;
	std::getline(input, dirs);
	
	std::map<std::string, StringPair> map{};
	std::string line;
	std::getline(input, line);
	while (std::getline(input, line)) {
		std::string start = line.substr(0, 3);
		std::string left = line.substr(7, 3);
		std::string right = line.substr(12, 3);
		map[start] = StringPair{left, right};
	}
	
	int dirI = 0;
	std::string curNode = "AAA";
	int length = 0;
	while (curNode != "ZZZ") {
		if (dirs[dirI] == 'L') {
			curNode = map[curNode].first;
		} else {
			curNode = map[curNode].second;
		}
		++dirI;
		dirI %= dirs.size();
		++length;
	}
	
	std::cout << length << '\n';
}