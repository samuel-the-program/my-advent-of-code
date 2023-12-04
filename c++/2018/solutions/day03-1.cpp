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

struct RectY {
	int y{};
	bool top{};
	Rect* rect{nullptr};
	int id{};
};

int rangeRectOverlap(std::vector<Rect>& rects) {
	struct XCoord {
		int x{};
		bool left{};
	};
	std::vector<XCoord> xScans{};
	for (Rect r : rects) {
		xScans.push_back(XCoord({r.x, true}));
		xScans.push_back(XCoord({r.x + r.w, false}));
	}
	std::sort(xScans.begin(), xScans.end(), [](XCoord& x1, XCoord& x2){
		return x1.x < x2.x;
	});
	
	int prevX{ 0 };
	int inside{ 0 };
	int overlap{ 0 };
	for (XCoord x : xScans) {
		if (inside >= 2) {
			overlap += x.x - prevX;
		}
		if (x.left) {
			++inside;
		} else {
			--inside;
		}
		prevX = x.x;
	}
	return overlap;
}

int main() {
	std::vector<Rect> rects{};
	std::ifstream input{ "../inputs/2018/day03-input.txt" };
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
	std::vector<RectY> scans{};
	
	for (int i{0}; i < rects.size(); ++i) {
		scans.push_back(RectY({rects[i].y, true, &rects[i], rects[i].id}));
		scans.push_back(RectY({rects[i].y + rects[i].h, false, &rects[i], rects[i].id}));
	}
	
	std::sort(scans.begin(), scans.end(), [](RectY& ry1, RectY& ry2){
		return ry1.y < ry2.y;
	});
	
	std::vector<Rect> curRects{};
	int prevY{ 0 };
	int area{ 0 };
	for (RectY ry : scans) {
		area += rangeRectOverlap(curRects) * (ry.y - prevY);
		if (ry.top) {
			curRects.push_back(*ry.rect);
		} else {
			auto it = std::remove_if(curRects.begin(), curRects.end(), [ry](Rect& r){
				return r.id == ry.id;
			});
			curRects.erase(it, curRects.end());
		}
		prevY = ry.y;
	}
	std::cout << area;
}

/*
Algorithm:
put top and bottom y-coords (hold reference to original rect, and whether top/bottom) in scans[]
currentRects = []
area = 0
for yLevel in scans:
	area += 1dRangeOverlap(currentRects) * (prevYLevel - yLevel)
	if yLevel is top:
		currentRects.push(yLevel.rect)
	else if yLevel is bottom:
		currentRects.remove(yLevel.rect)
return area;
*/