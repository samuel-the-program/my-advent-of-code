#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2018/day01-input.txt" };
	
	if (!input.is_open())
		std::cout << "failed to open file\n";
	
	std::string s{};
	int freq{ 0 };
	std::vector<int> resFreq{ };
	 while ( std::find(resFreq.begin(), resFreq.end(), freq) == resFreq.end() ) {
		resFreq.push_back(freq);
		std::getline(input, s);
		freq += std::stoi(s);
		
		if (input.eof()) {
			input.clear();
			input.seekg(0, std::ios::beg);
		}
	}
	std::cout << freq << '\n';
}