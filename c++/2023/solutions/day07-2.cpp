#include <iostream>
#include <fstream>
#include <string_view>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

enum HandType {
	fiveKind,
	fourKind,
	fullHouse,
	threeKind,
	twoPair,
	onePair,
	highCard
};

HandType findType(std::string_view hand) {
	std::map<char, int> charCounts{};
	int jokerCount = 0;
	for (char c : hand) {
		if (c == 'J') {
			++jokerCount;
		} else {
			++charCounts[c];
		}
	}
	std::vector<int> counts{};
	for (auto p : charCounts) {
		counts.push_back(p.second);
	};
	std::sort(counts.begin(), counts.end());
	std::reverse(counts.begin(), counts.end());
	if (counts.size() > 0) {
		counts[0] += jokerCount;
	} else {
		counts.push_back(jokerCount);
	}
	
	if (counts.size() == 1) {
		return fiveKind;
	} else if (counts.size() == 2) {
		if (counts[0] == 4) {
			return fourKind;
		} else if (counts[0] == 3) {
			return fullHouse;
		}
	} else if (counts.size() == 3) {
		if (counts[0] == 3) {
			return threeKind;
		} else if (counts[0] == 2) {
			return twoPair;
		}
	} else if (counts.size() == 4) {
		return onePair;
	}
	return highCard;
}

int higherCard(char c1, char c2) {
	static std::string cardOrder = "AKQT98765432J";
	if (c1 == c2) return 0;
	return cardOrder.find(c1) < cardOrder.find(c2) ? 1 : -1;
}

struct Hand {
	std::string cards{};
	int bid{};
	HandType type{ findType(cards) };
};

bool lowerHand(const Hand& h1, const Hand& h2) {
	if (h1.type != h2.type) return h2.type < h1.type;
	for (int i = 0; i < 5; ++i) {
		int comp = higherCard(h1.cards[i], h2.cards[i]);
		if (comp != 0) return comp == -1;
	};
	return true;
};

int main() {
	std::ifstream input{ "../inputs/2023/day07-input.txt" };
    if (!input.is_open()) std::cout << "file did not open\n";
	
	std::vector<Hand> allHands{};
	std::string line;
	while (std::getline(input, line)) {
		int pos = line.find(' ');
		allHands.push_back(Hand{
			line.substr(0, pos),
			std::stoi(line.substr(pos+1))
		});
	}
	
	std::sort(allHands.begin(), allHands.end(), lowerHand);
	int res = 0;
	for (int i = 0; i < allHands.size(); ++i) {
		res += allHands[i].bid * (i+1);
	}
	
	std::cout << res << '\n';
}