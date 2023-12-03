#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>

int nextMarble(std::vector<int>& marbles) {
	int next{ 1 };
	while ( std::find(marbles.begin(), marbles.end(), next) != marbles.end() ) ++next;
	return next;
}

int main() {
	std::ifstream input{ "inputs/day09-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	std::string s{};
	std::getline(input, s);
	
	std::regex r{ "(\\d+).+?(\\d+)" };
	std::smatch info;
	std::regex_search(s, info, r);
	
	const int numPlayers { std::stoi(info[1]) };
	const int maxMarbles { std::stoi(info[2]) };
	std::vector<int> players(numPlayers, 0);
	
	std::vector<int> marbles{ 0 };
	int curMarble{ 0 };
	int curPlayer{ 0 };
	int next { 1 };
	while (next != maxMarbles + 1) {
		if (next % 23 == 0) {
			int score { next };
			int removePos { static_cast<int>((curMarble + marbles.size() - 7) % marbles.size()) };
			score += marbles[removePos];
			marbles.erase(marbles.begin() + removePos);
			curMarble = removePos;
			players[curPlayer] += score;
		} else {
			int pos{ (curMarble + 2) % static_cast<int>(marbles.size()) };
			marbles.insert(marbles.begin() + pos, next);
			curMarble = pos;
		}
		
		++next;
		++curPlayer;
		curPlayer %= numPlayers;
	}
	
	std::cout << *(std::max_element(players.begin(), players.end())) << '\n';
}