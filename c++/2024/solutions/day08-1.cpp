#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

struct Coord {
    int x = 0;
    int y = 0;
};

bool operator==(const Coord& c1, const Coord& c2) {
    return c1.x == c2.x && c1.y == c2.y;
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

    std::vector<Coord> antinodes{};
    for (auto& pair : antennas) {
        char type = pair.first;
        std::vector<Coord>& coords = pair.second;

        for (int i = 0; i < coords.size(); ++i) {
            for (int j = i + 1; j < coords.size(); ++j) {
                Coord& a1 = coords[i];
                Coord& a2 = coords[j];
                Coord dist{a2.x - a1.x, a2.y - a1.y};
                
                Coord anti1{a1.x - dist.x, a1.y - dist.y};
                Coord anti2{a2.x + dist.x, a2.y + dist.y};

                if (anti1.x >= 0 && anti1.x < width && anti1.y >= 0 && anti1.y < height &&
                    std::find(antinodes.begin(), antinodes.end(), anti1) == antinodes.end()) {
                    antinodes.push_back(anti1);
                }
                if (anti2.x >= 0 && anti2.x < width && anti2.y >= 0 && anti2.y < height &&
                std::find(antinodes.begin(), antinodes.end(), anti2) == antinodes.end()) {
                    antinodes.push_back(anti2);
                }
            }
        }
    }
    /*for (const auto& c : antinodes) {
        std::cout << '(' << c.x << ", " << c.y << ") ";
    }*/
    std::cout << antinodes.size() << '\n';
}