#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>

int main() {
	std::ifstream input{ "../inputs/2023/day06-input.txt" };
	std::string times, distance;
	std::getline(input, times);
	std::getline(input, distance);
	
	std::vector<std::pair<int, int>> info{};
	for (int i = 10; i < distance.size(); i += 7) {
		info.push_back(std::pair<int, int>{
			std::stoi(times.substr(i, i + 6)),
			std::stoi(distance.substr(i, i + 6))
		});
	}
	
	/*
	T = total time
	R = record distance
	H = how long we hold
	
	H^2 - TH + R < 0
	a = 1
	b = -T
	c = R
	
	(-b +/- sqrt(b^2 - 4ac)) / 2a
	(T +/- sqrt(T^2 - 4*R)) / 2
	*/
	
	int res = 1;
	for (auto& p : info) {
		int t = p.first;
		int r = p.second;
		double dis = std::sqrt(t*t - 4*r);
		int smallest = std::ceil((t - dis) / 2);
		int biggest = std::floor((t + dis) / 2);
		
		res *= (biggest - smallest) + 1;
	}
	
	std::cout << res << '\n';
}