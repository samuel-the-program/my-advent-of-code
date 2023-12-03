#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <regex>
#include <algorithm>
#include <unordered_map>
#include <utility>

using Schedule = std::array<bool, 60>;

int main() {
	std::vector<std::string> lines{};
	
	std::ifstream input{ "inputs/day04-input.txt" };
	std::string s{};
	std::regex timeReg{ "\\[1518-(\\d+)-(\\d+) (\\d+):(\\d+)\\]" };
	while (std::getline(input, s)) {
		lines.push_back(s);
	}
	
	std::sort(lines.begin(), lines.end(), 
			[timeReg](std::string& s1, std::string& s2) {
				std::smatch m;
				std::regex_search(s1, m, timeReg);
				int month1{ std::stoi(m[1]) };
				int day1{ std::stoi(m[2]) };
				int hour1{ std::stoi(m[3]) };
				int min1{ std::stoi(m[4]) };
				
				std::regex_search(s2, m, timeReg);
				int month2{ std::stoi(m[1]) };
				int day2{ std::stoi(m[2]) };
				int hour2{ std::stoi(m[3]) };
				int min2{ std::stoi(m[4]) };
				
				if (month1 != month2) return month1 < month2;
				if (day1 != day2) return day1 < day2;
				if (hour1 != hour2) return hour1 < hour2;
				return min1 < min2;
			});
			
	std::cout << "Sorted " << lines.size() << '\n';
	
	std::unordered_map<int, std::unordered_map<std::string, Schedule>> guards{};
	std::regex parseReg{ "\\[1518-(\\d+-\\d+) \\d+:(\\d+)\\] (?:Guard #(\\d+)|(falls asleep|wakes up))" };
	int currentGuard{};
	int lastTime{};
	for (int i{0}; i < lines.size(); ++i) {
		std::smatch m;
		std::regex_search(lines[i], m, parseReg);
		if (m.length(3) > 0) {
			currentGuard = std::stoi(m[3]);
		} else if (m[4] == "falls asleep") {
			lastTime = std::stoi(m[2]);
		} else if (m[4] == "wakes up") {
			int curTime{ std::stoi(m[2]) };
			for (int i{ lastTime }; i < curTime; ++i) {
				guards[currentGuard][m[1]][i] = true;
			}
		}
	}
	
	std::unordered_map<int, std::array<int, 60>> flatGuards{};
	for (auto& guard : guards) {
		for (auto& schedule : guard.second) {
			for (int minute{ 0 }; minute < 60; ++minute) {
				if (schedule.second[minute]) ++flatGuards[guard.first][minute];
			}
		}
	}
	
	int maxGuard{};
	int maxMinute{};
	for (auto& guard : flatGuards) {
		auto maxIt{ std::max_element(guard.second.begin(), guard.second.end()) };
		if (*maxIt > flatGuards[maxGuard][maxMinute]) {
			maxGuard = guard.first;
			maxMinute = std::distance(guard.second.begin(), maxIt);
		}
	}
	std::cout << maxGuard * maxMinute << '\n';
}