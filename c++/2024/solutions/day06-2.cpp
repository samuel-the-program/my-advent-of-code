#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

struct Coord {
    int x = 0;
    int y = 0;
};
bool operator==(Coord a, Coord b) {
	return a.x == b.x && a.y == b.y;
}

bool validPos(int x, int y, const std::vector<std::string>& grid) {
    return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size();
}

int main() {
	std::ifstream input{ "../inputs/2024/day06-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    std::vector<std::string> grid{};
    Coord guardStart{};
    int i = 0;
	while (std::getline(input, s)) {
        if (s.find('^') != s.npos) {
            guardStart.x = s.find('^');
            guardStart.y = i;
        }
        grid.push_back(s);
        ++i;
	}

    int amount = 0;
    for (int i = 0; i < grid.size(); ++i) {
    std::cout << '#' << i << '\n';
    for (int j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == '#' || grid[i][j] == '^') continue;
        grid[i][j] = '#';

        bool inLoop = false;
        Coord guardPos = guardStart;
        Coord dir{0, -1};
        std::vector<std::pair<Coord, Coord>> path{};
        bool justTurned = false;
        while (validPos(guardPos.x, guardPos.y, grid)) {
            Coord nextPos{guardPos.x + dir.x, guardPos.y + dir.y};
            if (validPos(nextPos.x, nextPos.y, grid) && grid[nextPos.y][nextPos.x] == '#') {
                int temp = dir.x;
                dir.x = -dir.y;
                dir.y = temp;
                justTurned = true;
            } else {
                if (justTurned && std::find(path.begin(), path.end(), 
                std::pair<Coord, Coord>{guardPos, dir}) != path.end()) {
                    inLoop = true;
                    break;
                }
                justTurned = false;
                //std::cout << guardPos.x << ' ' << guardPos.y << '\n';
                path.push_back({guardPos, dir});
                grid[guardPos.y][guardPos.x] = 'X';
                guardPos = nextPos;
            }
        }
        if (inLoop) {
            ++amount;
        }

        grid[i][j] = '.';
    }
    }
    std::cout << amount << '\n';
}