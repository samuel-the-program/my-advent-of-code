#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>

class Rect {
public:
	int id{};
	int x{};
	int y{};
	int w{};
	int h{};
};

bool rectOverlap(Rect& r1, Rect& r2) {
	if (r1.x > r2.x + r2.w || r2.x > r1.x + r1.w) return false;
	if (r1.y > r2.y + r2.h || r2.y > r1.y + r1.h) return false;
	return true;
}

int main() {
	std::vector<Rect> rects{};
	std::ifstream input{ "inputs/day03-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::string s{};
	while (std::getline(input, s)){
		const std::regex parseReg{ "#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)" };
		std::smatch m;
		std::regex_search(s, m, parseReg);
		rects.push_back({
			std::stoi(m[1]),
			std::stoi(m[2]),
			std::stoi(m[3]),
			std::stoi(m[4]),
			std::stoi(m[5]),
		});
	}
	
	for (int i{0}; i < rects.size(); ++i) {
		Rect r{ rects[i] };
		bool overlap{ false };
		for (int j{0}; j < rects.size(); ++j) {
			Rect other{ rects[j] };
			if (i == j) continue;
			if (rectOverlap(r, other)) {
				overlap = true;
				break;
			}
		}
		if (!overlap) {
			std::cout << r.id << '\n';
			break;
		}
	}
}