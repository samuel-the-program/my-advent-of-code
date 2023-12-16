#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2023/day06-input.txt" };
	std::string times, distance;
	std::getline(input, times);
	std::getline(input, distance);
	
	times = times.substr(10);
	distance = distance.substr(10);
	times.erase(std::remove(times.begin(), times.end(), ' '), times.end());
	distance.erase(std::remove(distance.begin(), distance.end(), ' '), distance.end());
	long long t = std::stoll(times);
	long long r = std::stoll(distance);
	
	double dis = std::sqrt(t*t - 4*r);
	long long smallest = std::ceil((t - dis) / 2);
	long long biggest = std::floor((t + dis) / 2);
	
	std::cout << (biggest - smallest) + 1 << '\n';
}