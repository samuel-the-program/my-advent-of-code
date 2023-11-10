#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <fstream>
#include <vector>

int similar(std::string_view s1, std::string_view s2) {
	int foundDiff{ -1 };
	for (int i{0}; i < s1.size(); ++i) {
		if (s1[i] != s2[i]) {
			if (foundDiff != -1) {
				return -1;
			} else {
				foundDiff = i;
			}
		}
	}
	return foundDiff;
}

int main() {
	std::ifstream input{"inputs/day02-input.txt"};
	if (!input.is_open()) std::cout << "file not open\n";
	
	//std::cout << similar("abcdefghijllmnop", "abcdefghijklmnop");
	
	std::vector<std::string> ids(250);
	std::string s{};
	while ( std::getline(input, s) ) {
		ids.push_back(s);
	}
	
	for (int i{0}; i < ids.size() - 1; ++i) {
		for (int j{i+1}; j < ids.size(); ++j) {
			if (similar(ids[i], ids[j]) != -1) {
				std::string s{ ids[i] };
				s.erase(similar(ids[i], ids[j]), 1);
				std::cout << s << '\n';
				std::cout << "Codes: \t" << ids[i] << 
							 "\n\t" << ids[j] << '\n';
				break;
			}
		}
	}
}