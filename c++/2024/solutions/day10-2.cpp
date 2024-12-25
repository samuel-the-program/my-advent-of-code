#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

struct Coord {
    int x = 0;
    int y = 0;
};

bool operator==(const Coord& c1, const Coord& c2) {
    return c1.x == c2.x && c1.y == c2.y;
}
bool operator<(const Coord& c1, const Coord& c2) {
    if (c1.x != c2.x) return c1.x < c2.x;
    return c1.y < c2.y;
}

std::ostream& operator<<(std::ostream& os, const Coord& c) {
    os << '(' << c.x << ", " << c.y << ')';
    return os;
}

std::set<Coord> visited{};
int dfs(const Coord& cur, 
        std::vector<std::string>& grid,
        std::map<Coord, std::vector<Coord>>& graph) {
    if (grid[cur.y][cur.x] == '9') return 1;
    visited.insert(cur);
    int sum = 0;
    for (Coord& neighbour : graph[cur]) {
        if (visited.find(neighbour) == visited.end()) {
            sum += dfs(neighbour, grid, graph);
        }
    }
    visited.erase(cur);
    return sum;
}

int main() {
	std::ifstream input{ "../inputs/2024/day10-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    std::vector<std::string> grid{};
	while (std::getline(input, s)) {
        grid.push_back(s);
	}

    std::map<Coord, std::vector<Coord>> graph{};
    std::vector<Coord> zeroes{};
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            Coord c{x, y};
            char height = grid[y][x];
            if (height == '0') {
                zeroes.push_back(c);
            }
            if (y != 0 && grid[y - 1][x] - height == 1) {
                graph[c].push_back(Coord{x, y - 1});
            }
            if (y != grid.size() - 1 && grid[y + 1][x] - height == 1) {
                graph[c].push_back(Coord{x, y + 1});
            }
            if (x != 0 && grid[y][x - 1] - height == 1) {
                graph[c].push_back(Coord{x - 1, y});
            }
            if (x != grid[y].size() - 1 && grid[y][x + 1] - height == 1) {
                graph[c].push_back(Coord{x + 1, y});
            }
        }
    }

    int sumRatings = 0;
    for (const Coord& c : zeroes) {
        sumRatings += dfs(c, grid, graph);
    }

    std::cout << sumRatings << '\n';
}