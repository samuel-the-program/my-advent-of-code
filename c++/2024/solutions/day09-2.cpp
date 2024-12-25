#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

struct Range {
    int id = -1;
    int start = 0;
    int size = 0;
};

int main() {
	std::ifstream input{ "../inputs/2024/day09-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
	input >> s;
    bool file = true;
    std::vector<Range> files{};
    std::vector<Range> freeSpace{};
    int fileId = 0;
    int pos = 0;
    for (char c : s) {
        int size = c - 48;
        if (file) {
            files.push_back(Range{fileId, pos, size});
            pos += size;
            ++fileId;
        } else {
            freeSpace.push_back(Range{-1, pos, size});
            pos += size;
        }
        file = !file;
    }

    for (int i = files.size() - 1; i >= 0; --i) {
        /*for (Range& file : files) {
            std::cout << file.id << ' ' << file.start << ' ' << file.size << '\n';
        }
        for (Range& free : freeSpace) {
            std::cout << free.id << ' ' << free.start << ' ' << free.size << '\n';
        }
        std::cout << '\n';*/

        Range& curFile = files[i];
        int freeI = 0;
        bool found = false;
        for (; freeI < freeSpace.size(); ++freeI) {
            Range& curFree = freeSpace[freeI];
            if (curFree.start > curFile.start) break;
            if (curFree.size >= curFile.size) {
                found = true;
                break;
            }
        }
        if (found) {
            Range& curFree = freeSpace[freeI];
            if (curFile.size == curFree.size) {
                curFile.start = curFree.start;
                freeSpace.erase(freeSpace.begin() + freeI);
            } else {
                curFile.start = curFree.start;
                Range newFree{-1, curFree.start + curFile.size, curFree.size - curFile.size};
                curFree.id = curFile.id;
                freeSpace.erase(freeSpace.begin() + freeI);
                freeSpace.insert(freeSpace.begin() + freeI, newFree);
            }
        }
    }
    std::cout << "Done rearranging\n";

    std::sort(files.begin(), files.end(), 
        [](const Range& a, const Range& b){ return a.start < b.start; });
    std::cout << "Done sorting\n";

    long long total = 0;
    for (Range& file : files) {
        total += file.id * file.size * 0.5 * (2 * file.start + file.size - 1);
    }
    std::cout << total << '\n';
}