#include <iostream>
#include <vector>
#include "../../aoc-utils.h"

int main() {
	auto v = AocUtils::split("10,,13,,16,,21,,3,,45", ",,");
	std::cout << v << '\n';
}