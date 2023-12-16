#pragma once

#include <vector>
#include <string>
#include <ostream>

namespace AocUtils {
	std::vector<std::string> split(std::string s, std::string delimiter);
	std::vector<std::string> split(std::string s, char delimiter);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
	if (vec.size() == 0) {
		out << "[]";
		return out;
	}
	
	out << '[' << vec[0];
	for (int i = 1; i < vec.size(); ++i) {
		out << ", " << vec[i];
	}
	out << ']';
	return out;
}