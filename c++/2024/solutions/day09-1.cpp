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

    int freeI = 0;
    for (int i = files.size() - 1; i >= 0; --i) {
        Range& curFile = files[i];
        Range& curFree = freeSpace[freeI];
        if (curFree.start > curFile.start) break;
        if (curFile.size == curFree.size) {
            curFree.id = curFile.id;
            files.erase(files.begin() + i);
            ++freeI;
        } else if (curFile.size < curFree.size) {
            Range newFree{-1, curFree.start + curFile.size, curFree.size - curFile.size};
            curFree.id = curFile.id;
            curFree.size = curFile.size;
            files.erase(files.begin() + i);
            freeSpace.insert(freeSpace.begin() + freeI + 1, newFree);
            ++freeI;
        } else if (curFile.size > curFree.size) {
            curFree.id = curFile.id;
            curFile.size = curFile.size - curFree.size;
            ++i;
            ++freeI;
        }
    }
    std::cout << "Done rearranging\n";

    std::vector<Range> newFiles = files;
    for (Range& free : freeSpace) {
        if (free.id != -1) {
            newFiles.push_back(free);
        } else {
            break;
        }
    }
    std::sort(newFiles.begin(), newFiles.end(), 
        [](const Range& a, const Range& b){ return a.start < b.start; });
    std::cout << "Done sorting\n";

    long long total = 0;
    for (Range& file : newFiles) {
        total += file.id * file.size * 0.5 * (2 * file.start + file.size - 1);
    }
    std::cout << total << '\n';
}