#include <iostream>
#include <fstream>
#include <vector>
#include "../../aoc-utils.h"
#include <algorithm>
#include <cmath>

struct Coord {
	int x{};
	int y{};
};

int main() {
	std::ifstream input{ "../inputs/2023/day11-input.txt "};
	int expansion = 1000000;
	
	std::vector<Coord> galaxies{};
	std::vector<int> emptyRows{};
	std::vector<int> emptyCols{};
	std::vector<bool> colState{};
	std::string line;
	for(int i = 0; std::getline(input, line); ++i) {
		int pos = -1;
		bool emptyRow = true;
		while ((pos = line.find('#', pos+1)) != line.npos) {
			emptyRow = false;
			galaxies.push_back(Coord{pos, i});
		}
		if (emptyRow) emptyRows.push_back(i);
		for (int j = 0; j < line.size(); ++j) {
			if (i == 0) {
				colState.push_back(line[j] != '#');
			} else {
				if (line[j] == '#') colState[j] = false;
			}
		}
	}
	for (int j = 0; j < colState.size(); ++j) {
		if(colState[j]) emptyCols.push_back(j);
	}
	
	long long res = 0;
	for (int i = 0; i < galaxies.size() - 1; ++i) {
		for (int j = i+1; j < galaxies.size(); ++j) {
			Coord& g1 = galaxies[i];
			Coord& g2 = galaxies[j];
			int rowsBetween = std::count_if(emptyRows.begin(), emptyRows.end(),
				[&g1, &g2](int r){ return r > std::min(g1.y, g2.y) && r < std::max(g1.y, g2.y); });
			int colsBetween = std::count_if(emptyCols.begin(), emptyCols.end(),
				[&g1, &g2](int c){ return c > std::min(g1.x, g2.x) && c < std::max(g1.x, g2.x); });
			res += std::abs(g1.x - g2.x) + std::abs(g1.y - g2.y) + (rowsBetween + colsBetween)*(expansion-1);
		}
	}
	
	std::cout << res << '\n';
}