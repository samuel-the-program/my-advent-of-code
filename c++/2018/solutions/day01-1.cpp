#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::ifstream input{ "../inputs/2018/day01-input.txt" };
	
	if (!input.is_open())
		std::cout << "failed to open file\n";
	
	std::string s{};
	int freq{ 0 };
	while ( std::getline(input, s) ) {
		freq += std::stoi(s);
	}
	std::cout << freq << '\n';
}