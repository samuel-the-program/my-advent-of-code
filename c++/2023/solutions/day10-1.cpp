#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

using Coord = std::pair<int, int>;
// Coord.first = x-coord, .second = y-coord

bool valid(Coord& c, int w, int h) {
	return c.first >= 0 && c.first <= w
	    && c.second >= 0 && c.second <= h;
}

int main() {
	std::ifstream input{ "../inputs/2023/day10-input.txt" };
	
	std::vector<std::string> grid{};
	std::string line;
	Coord start{};
	int i = 0;
	while (std::getline(input, line)) {
		grid.push_back(line);
		if (line.find('S') != line.npos) {
			start.first = line.find('S');
			start.second = i;
		}
		++i;
	}
	
	std::map<char, std::vector<Coord>> dirs{
		{ '|', { {0, -1}, {0, 1} } },
		{ '-', { {-1, 0}, {1, 0} } },
		{ 'L', { {0, -1}, {1, 0} } },
		{ 'J', { {0, -1}, {-1, 0} } },
		{ '7', { {0, 1}, {-1, 0} } },
		{ 'F', { {0, 1}, {1, 0} } },
		{ '.', {} },
		{ 'S', {} }
	};
	
	std::vector<Coord> loopStarts{
		{-1, 0}, {1, 0}, {0, -1}, {0, 1}
	};
	
	for (Coord& s : loopStarts) {
		Coord curCoord {start.first + s.first, start.second + s.second};
		Coord prevDir = s;
		std::vector<Coord> path{};
		while (valid(curCoord, grid[0].size(), grid.size()) && curCoord != start) {
			path.push_back(curCoord);
			Coord removeDir{ -prevDir.first, -prevDir.second };
			auto ds = dirs[grid[curCoord.second][curCoord.first]];
			if (ds.size() == 0 || 
			  std::find(ds.begin(), ds.end(), removeDir) == ds.end()) {
				break;
			}
			
			Coord nextDir{};
			if (ds[0] == removeDir) {
				nextDir = ds[1];
			} else {
				nextDir = ds[00];
			}
			
			curCoord = {curCoord.first + nextDir.first, curCoord.second + nextDir.second};
			prevDir = nextDir;
		}
		
		if (path.size() > 1) {
			std::cout << (path.size()+1)/2 << '\n';
			break;
		}
	}
}