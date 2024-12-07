#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

int main() {
	std::ifstream input{ "../inputs/2024/day05-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
    std::string s;
    std::map<int, std::vector<int>> order{};
    // if order[i].includes(j), j must come before i
	while (std::getline(input, s) && s != "") {
        int page1 = std::stoi(s.substr(0, s.find('|')));
        int page2 = std::stoi(s.substr(s.find('|') + 1));
        order[page2].push_back(page1);
	}

    int result = 0;
    while (std::getline(input, s)) {
        size_t posStart = 0, posEnd;
		std::string token;
		std::vector<int> pageList{};

		while ((posEnd = s.find(',', posStart)) != std::string::npos) {
			token = s.substr(posStart, posEnd - posStart);
			posStart = posEnd + 1;
			pageList.push_back(std::stoi(token));
		}
		pageList.push_back(std::stoi(s.substr(posStart)));

        bool valid = true;
        for (int i = 0; i < pageList.size() - 1; ++i) {
            for (int j = i + 1; j < pageList.size(); ++j) {
                std::vector<int>& beforeI = order[pageList[i]];
                if (std::find(beforeI.begin(), beforeI.end(), pageList[j]) != beforeI.end()) {
                    valid = false;
                    int pageJ = pageList[j];
                    pageList.erase(pageList.begin() + j);
                    pageList.insert(pageList.begin() + i, pageJ);
                }
            }
        }
        if (!valid) {
            result += pageList[pageList.size()/2];
        }
	}
    std::cout << result << '\n';
}