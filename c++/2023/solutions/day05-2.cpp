#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/* Algorithm:
Treat seed ranges like real ranges
Check when seed ranges and map ranges overlap
Remove the overlap range from seed range and make it a new seed range
Find the lowest range
*/

struct Map {
	long long destStart{};
	long long srcStart{};
	long long length{};
};

struct Range {
	long long start{};
	long long end{};
	bool mapped{ false };
};

std::vector<Range> mapFunc(Range& r, Map& m, bool& changed) {
	if (r.mapped) {
		changed = false;
		return std::vector<Range>{};
	}
	long long diff = m.destStart - m.srcStart;
	long long mEnd = m.srcStart + m.length - 1;
	if (m.srcStart <= r.start && r.end <= mEnd) {
		changed = true;
		return std::vector<Range>{Range{r.start + diff, r.end + diff, true}};
	} else if (r.start < m.srcStart && mEnd < r.end) {
		changed = true;
		return std::vector<Range>{
			Range{r.start, m.srcStart - 1, false},
			Range{m.srcStart + diff, mEnd + diff, true},
			Range{mEnd + 1, r.end, false}
		};
	} else if (r.start < m.srcStart && m.srcStart < r.end) {
		changed = true;
		return std::vector<Range>{
			Range{r.start, m.srcStart-1, false},
			Range{m.srcStart + diff, r.end + diff, true}
		};
	} else if (r.start < mEnd && mEnd < r.end) {
		changed = true;
		return std::vector<Range>{
			Range{r.start + diff, mEnd + diff, true},
			Range{mEnd + 1, r.end, false}
		};
	} else {
		changed = false;
		return std::vector<Range>{};
	}
};

int main() {
	std::ifstream input{ "../inputs/2023/day05-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::string seedsStr;
	std::getline(input, seedsStr);
	seedsStr = seedsStr.substr(7);
	
	std::vector<Range> seeds{};
	int pos = seedsStr.find(' ');
	while (pos != seedsStr.npos) {
		long long start = std::stoll(seedsStr.substr(0, pos));
		int lastPos = pos;
		pos = seedsStr.find(' ', lastPos + 1);
		pos = pos == seedsStr.npos ? seedsStr.size() - 1 : pos;
		long long count = std::stoll(seedsStr.substr(lastPos+1, pos));
		seeds.push_back(Range{start, start + count});
		seedsStr = seedsStr.substr(pos + 1);
		pos = seedsStr.find(' ');
	}
	
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
	
	std::vector<std::vector<Range>> locations{};
	for (Range& r : seeds) {
		std::vector<Range> curSeeds{ r };
		for (auto& mapV : fullMap) {
			for (auto& m : mapV) {
				bool changed = false;
				for (int i = 0; i < curSeeds.size(); ++i) {
					auto res = mapFunc(curSeeds[i], m, changed);
					if (changed) {
						curSeeds.erase(curSeeds.begin() + i);
						curSeeds.insert(curSeeds.begin() + i, res.begin(), res.end());
					}
				}
			}
			for (auto& c : curSeeds) c.mapped = false;
		}
		locations.push_back(curSeeds);
	}
	
	long long minLoc = locations[0][0].start;
	for (auto& v : locations) {
		for (auto& c : v) {
			if (c.start < minLoc) minLoc = c.start;
		}
	}
	std::cout << minLoc << '\n';
}