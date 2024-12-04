#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

std::string word = "XMAS";
int wordI = -1;
std::string revWord = "SAMX";
int revWordI = -1;
int count = 0;
bool updateCheck(char curChar) {
    if (wordI == -1) {
        if (curChar == word[0]) {
            wordI = 1;
        }
    } else {
        if (wordI == word.size() - 1 && curChar == word[wordI]) {
            ++count;
            wordI = -1;
            return true;
        } else if (curChar == word[wordI]) {
            ++wordI;
        } else {
            wordI = -1;
            return updateCheck(curChar);
        }
    }

    if (revWordI == -1) {
        if (curChar == revWord[0]) {
            revWordI = 1;
        }
    } else {
        if (revWordI == revWord.size() - 1 && curChar == revWord[revWordI]) {
            ++count;
            revWordI = -1;
            return true;
        } else if (curChar == revWord[revWordI]) {
            ++revWordI;
        } else {
            revWordI = -1;
            return updateCheck(curChar);
        }
    }
    return false;
}

int main() {
	std::ifstream input{ "../inputs/2024/day04-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::vector<std::string> grid{};
    std::string s;
	while (std::getline(input, s)) {
        grid.push_back(s);
    }

    int count = 0;

    // Horizontal
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (updateCheck(grid[i][j])) {
                ++count;
                //std::cout << i << ' ' << j << '\n';
                --j;
            }
        }
        wordI = -1;
        revWordI = -1;
    }

    // Vertical
    for (int j = 0; j < grid[0].size(); ++j) {
        for (int i = 0; i < grid.size(); ++i) {
            if (updateCheck(grid[i][j])) {
                ++count;
                //std::cout << i << ' ' << j << '\n';
                --i;
            }
        }
        wordI = -1;
        revWordI = -1;
    }

    // Diagonal /
    for (int n = 0; n < grid[0].size(); ++n) {
        int i = 0;
        for (int j = n; j >= 0 && i < grid.size(); --j) {
            if (updateCheck(grid[i][j])) {
                ++count;
                //std::cout << i << ' ' << j << '\n';
                --i;
                ++j;
            }
            ++i;
        }
        wordI = -1;
        revWordI = -1;
    }
    for (int n = 1; n < grid.size(); ++n) {
        int j = grid[0].size() - 1;
        for (int i = n; i < grid.size() && j >= 0; ++i) {
            if (updateCheck(grid[i][j])) {
                ++count;
                //std::cout << i << ' ' << j << '\n';
                --i;
                ++j;
            }
            --j;
        }
        wordI = -1;
        revWordI = -1;
    }

    // Diagonal left
    for (int n = 0; n < grid.size(); ++n) {
        int j = 0;
        for (int i = n; i < grid.size() && j < grid[0].size(); ++i) {
            if (updateCheck(grid[i][j])) {
                ++count;
                //std::cout << i << ' ' << j << '\n';
                --i;
                --j;
            }
            ++j;
        }
        wordI = -1;
        revWordI = -1;
    }
    for (int n = 1; n < grid[0].size(); ++n) {
        int i = 0;
        for (int j = n; j < grid[0].size() && i < grid.size(); ++j) {
            if (updateCheck(grid[i][j])) {
                ++count;
                //std::cout << i << ' ' << j << '\n';
                --i;
                --j;
            }
            ++i;
        }
        wordI = -1;
        revWordI = -1;
    }
    std::cout << count << '\n';
}