#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

struct Coord {
    int x = 0;
    int y = 0;
};

bool operator==(const Coord& a, const Coord& b) {
	return a.x == b.x && a.y == b.y;
}

bool operator<(const Coord& a, const Coord& b) {
	if (a.x != b.x) return a.x < b.x;
    return a.y < b.y; 
}

bool validPos(int x, int y, const std::vector<std::string>& grid) {
    return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size();
}

int main() {
	std::ifstream input{ "../inputs/2024/day06-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    std::vector<std::string> grid{};
    Coord guardPos{};
    int i = 0;
	while (std::getline(input, s)) {
        if (s.find('^') != s.npos) {
            guardPos.x = s.find('^');
            guardPos.y = i;
        }
        grid.push_back(s);
        ++i;
	}

    Coord dir{0, -1};
    std::set<Coord> path{};
    while (validPos(guardPos.x, guardPos.y, grid)) {
        Coord nextPos{guardPos.x + dir.x, guardPos.y + dir.y};
        if (validPos(nextPos.x, nextPos.y, grid) && grid[nextPos.y][nextPos.x] == '#') {
            int temp = dir.x;
            dir.x = -dir.y;
            dir.y = temp;
        } else {
            path.insert(guardPos);
            grid[guardPos.y][guardPos.x] = 'X';
            guardPos = nextPos;
        }
    }
    std::cout << path.size() << '\n';
}