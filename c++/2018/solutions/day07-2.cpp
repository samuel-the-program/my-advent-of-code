#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

struct Worker {
	char curStep{};
	int finishTime{};
};

void printWorkers(const std::vector<Worker>& arr) {
	int i{1};
	for (const Worker& w : arr) {
		std::cout << 'W' << i << ": " << w.curStep << ' ' << w.finishTime << '\n';
		++i;
	}
}

int amtWorkers{ 5 };
int addedTime{ 60 };

int main() {
	std::unordered_map<char, std::vector<char>> depends{};
	std::unordered_map<char, bool> finished{};
	std::set<char> steps{};
	std::vector<char> completedSteps{};
	std::ifstream input{ "../inputs/2018/day07-input.txt" };
	if (!input.is_open()) std::cout << "file is not open\n";
	
	std::string s{};
	while (std::getline(input, s)) {
		depends[s[36]].push_back(s[5]);
		if (!depends.count(s[5])) depends[s[5]] = {};
		
		steps.insert(s[5]);
		steps.insert(s[36]);
	}
	
	std::vector<Worker> workers( amtWorkers, {'#', 0} );
	std::unordered_map<char, bool> inProgress{};
	int curTime{ 0 };
	
	while (completedSteps.size() < depends.size()) {
		for (Worker& w : workers) {
			if (w.curStep != '#') continue;
			std::vector<char> available{};
			for (char step : steps) {
				if (finished[step] || inProgress[step]) continue;
				bool prereqsComplete{ true };
				for (char prereq : depends[step]) {
					if (!finished[prereq]) {
						prereqsComplete = false;
						break;
					}
				}
				if (prereqsComplete) available.push_back(step);
			}
			if (available.size() > 0) {
				char chosenStep{ *std::min_element(available.begin(), available.end()) };
				w.curStep = chosenStep;
				w.finishTime = curTime + chosenStep - 'A' + 1 + addedTime;
				inProgress[chosenStep] = true;
			} else {
				w.curStep = '#';
			}
		}
		
		int nextTime{ curTime + 100 };
		for (const Worker& w : workers) {
			if (w.curStep == '#') continue;
			if (w.finishTime < nextTime) nextTime = w.finishTime;
		}
		
		for (Worker& w : workers) {
			if (w.curStep == '#') continue;
			if (w.finishTime <= nextTime) {
				finished[w.curStep] = true;
				inProgress[w.curStep] = false;
				completedSteps.push_back(w.curStep);
				w.curStep = '#';
			}
		}
		curTime = nextTime;
	}
	std::cout << curTime << '\n';
}

/*
int curTime{};
struct Worker {
	char curStep{};
	int finishTime{};
}
*/