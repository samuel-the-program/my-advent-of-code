#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

int abs(int x) {
	return (x < 0 ? -x : x);
}

struct Point {
	int x{};
	int y{};
	int cellArea{};
	bool infinite{};
};

Point toPoint(std::string& s) {
	int comma{ static_cast<int>(s.find(',')) };
	
	return { std::stoi(s.substr(0, comma)),
			 std::stoi(s.substr(comma + 2)) };
}

void printPoint(const Point& p) {
	std::cout << '(' << p.x << ", " << p.y << ')';
}

bool equalsPoint(const Point& p1, const Point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

int distPoint(const Point& p1, const Point& p2) {
	return abs(p1.x-p2.x) + abs(p1.y-p2.y);
}

int closestPoint(const Point& checkPoint, std::vector<Point>& points) {
	std::vector<int> dists{};
	for (const Point& p : points) {
		dists.push_back(distPoint(checkPoint, p));
	}
	
	auto minIt{ std::min_element(dists.begin(), dists.end()) };
	if (std::count(dists.begin(), dists.end(), *minIt) > 1) return -1;
	return std::distance(dists.begin(), minIt);
}

int main() {
	std::ifstream input{ "inputs/day06-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	std::vector<Point> points{};
	std::string s{};
	while (std::getline(input, s)) {
		points.push_back(toPoint(s));
	}
	
	Point topLeft{ points[0] };
	Point bottomRight{ points[0] };
	for (const Point& p : points) {
		if (p.x <= topLeft.x) topLeft.x = p.x - 1;
		if (p.y <= topLeft.y) topLeft.y = p.y - 1;
		if (p.x >= bottomRight.x) bottomRight.x = p.x + 1;
		if (p.y >= bottomRight.y) bottomRight.y = p.y + 1;
	}
	
	for (int x{ topLeft.x }; x <= bottomRight.x; ++x) {
		for (int y{ topLeft.y }; y <= bottomRight.y; ++y) {
			int closestI{ closestPoint(Point{x, y}, points) };
			if (closestI == -1 || points[closestI].infinite) continue;
			if (x == topLeft.x || y == topLeft.y ||
			x == bottomRight.x || y == bottomRight.y) {
				points[closestI].infinite = true;
				continue;
			}
			++points[closestI].cellArea;
		}
	}
	
	auto remIt{ std::remove_if(points.begin(), points.end(), [](const Point& p){return p.infinite;}) };
	points.erase(remIt, points.end());
	
	auto maxIt{ std::max_element(points.begin(), points.end(), 
		[](const Point& p1, const Point& p2) {
			return p1.cellArea < p2.cellArea;
		})
	};
	
	std::cout << maxIt->cellArea << '\n';
}