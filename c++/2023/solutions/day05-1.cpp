#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Map {
	long long destStart{};
	long long srcStart{};
	long long length{};
};

int main() {
	std::ifstream input{ "../inputs/2023/day05-input.txt" };
	
	std::string seedsStr;
	std::getline(input, seedsStr);
	seedsStr = seedsStr.substr(7);
	
	std::vector<long long> seeds{};
	int pos = seedsStr.find(' ');
	while (pos != seedsStr.npos) {
		seeds.push_back(std::stoll(seedsStr.substr(0, pos)));
		seedsStr = seedsStr.substr(pos + 1);
		pos = seedsStr.find(' ');
	}
	seeds.push_back(std::stoll(seedsStr.substr(pos + 1)));
	
	std::vector<std::vector<Map>> fullMap{{}};
	std::string line;
	int mapIndex = 0;
	std::getline(input, line);
	while (std::getline(input, line)) {
		if (line.size() < 2) {
			fullMap.push_back(std::vector<Map>{});
			++mapIndex;
		} else if (line[0] >= '0' && line[0] <= '9') {
			int firstSpace = line.find(' ');
			int secondSpace = line.find(' ', firstSpace+1);
			Map m {
				std::stoll(line.substr(0, firstSpace)),
				std::stoll(line.substr(firstSpace+1, secondSpace)),
				std::stoll(line.substr(secondSpace+1))
			};
			fullMap[mapIndex].push_back(m);
		}
	}
	
	std::vector<long long> locations{};
	for (long long seed : seeds) {
		for (auto& mapV : fullMap) {
			for (Map& m : mapV) {
				if (seed >= m.srcStart && seed <= m.srcStart + m.length) {
					seed += m.destStart - m.srcStart;
					break;
				}
			}
		}
		locations.push_back(seed);
	}
	
	std::cout << *std::min_element(locations.begin(), locations.end()) << '\n';
}