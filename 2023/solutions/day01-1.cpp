#include <iostream>
#include <fstream>

int main() {
	std::ifstream input{ "2023/inputs/day01-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::cout << "It works!";
}