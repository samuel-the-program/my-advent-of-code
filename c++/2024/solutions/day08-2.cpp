#include <iostream>
#include <string>
#include <fstream>
#include <vector>
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

int main() {
	std::ifstream input{ "../inputs/2024/day08-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    std::map<char, std::vector<Coord>> antennas{};
    int i = 0;
    int w = 0;
	while (std::getline(input, s)) {
        w = s.size();
        for (int j = 0; j < w; ++j) {
            if (s[j] != '.') {
                antennas[s[j]].push_back(Coord{j, i});
            }
        }
        ++i;
	}
    const int width = w;
    const int height = i;

    std::set<Coord> antinodes{};
    for (auto& pair : antennas) {
        char type = pair.first;
        std::vector<Coord>& coords = pair.second;

        for (int i = 0; i < coords.size(); ++i) {
            for (int j = i + 1; j < coords.size(); ++j) {
                Coord& a1 = coords[i];
                Coord& a2 = coords[j];
                Coord dist{a2.x - a1.x, a2.y - a1.y};
                
                antinodes.insert(a1);
                antinodes.insert(a2);
                
                Coord anti1{a1.x - dist.x, a1.y - dist.y};
                while (anti1.x >= 0 && anti1.x < width && anti1.y >= 0 && anti1.y < height) {
                    antinodes.insert(anti1);
                    anti1.x -= dist.x;
                    anti1.y -= dist.y;
                }

                Coord anti2{a2.x + dist.x, a2.y + dist.y};
                while (anti2.x >= 0 && anti2.x < width && anti2.y >= 0 && anti2.y < height) {
                    antinodes.insert(anti2);
                    anti2.x += dist.x;
                    anti2.y += dist.y;
                }
            }
        }
    }

    std::cout << antinodes.size() << '\n';
}