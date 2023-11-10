#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

int main() {
	std::unordered_map<char, std::vector<char>> depends{};
	std::unordered_map<char, bool> finished{};
	std::set<char> steps{};
	std::vector<char> completedSteps{};
	std::ifstream input{ "inputs/day07-input.txt" };
	if (!input.is_open()) std::cout << "file is not open\n";
	
	std::string s{};
	while (std::getline(input, s)) {
		depends[s[36]].push_back(s[5]);
		if (!depends.count(s[5])) depends[s[5]] = {};
		
		steps.insert(s[5]);
		steps.insert(s[36]);
	}
	
	while (completedSteps.size() < depends.size()) {
		std::vector<char> available{};
		for (char step : steps) {
			bool prereqsComplete{ true };
			for (char prereq : depends[step]) {
				if (!finished[prereq]) {
					prereqsComplete = false;
					break;
				}
			}
			if (prereqsComplete) {
				available.push_back(step);
			}
		}
		char chosenStep{ *std::min_element(available.begin(), available.end()) };
		
		completedSteps.push_back(chosenStep);
		finished[chosenStep] = true;
		steps.erase(std::find(steps.begin(), steps.end(), chosenStep));
	}
	for (char c : completedSteps) {
		std::cout << c;
	}
	std::cout << '\n';
}

/*
Data structure: map from each step to its dependencies
std::unordered_map<char, std::vector<char>>

Algorithm:
1. Parse input
2. While there are steps left
	a) Initialise available (std::vector<char>)
	b) For all steps
		i) If ALL step's requirements are completed, add to available
	c) Pick first alphabetically (min_element)
	d) Add to completed list
	e) Mark steps as completed
3. Output list
*/