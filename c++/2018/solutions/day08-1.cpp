#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int globalID{ 0 };

struct Node {
	std::vector<int> children{};
	std::vector<int> metadata{};
	int ID{ globalID++ };
};

int createNodes(std::vector<Node>& nodes, std::ifstream& tree) {
	Node n{};
	int numChild{};
	int numMeta{};
	tree >> numChild;
	tree >> numMeta;
	for (int i{0}; i < numChild; ++i) {
		int childNode{ createNodes(nodes, tree) };
		n.children.push_back(childNode);
	}
	for (int i{0}; i < numMeta; ++i) {
		int meta{};
		tree >> meta;
		n.metadata.push_back(meta);
	}
	nodes.push_back(n);
	return n.ID;
}

int main() {
	std::ifstream input{ "inputs/day08-input.txt" };
	if (!input.is_open()) std::cout << "file did not open\n";
	
	std::vector<Node> nodes{};
	createNodes(nodes, input);
	std::sort(nodes.begin(), nodes.end(),
		[](const Node& n1, const Node& n2) {
			return n1.ID < n2.ID;
		}
	);
	
	int sum{};
	for (const Node& n : nodes) {
		for (int meta : n.metadata) {
			sum += meta;
		}
	}
	std::cout << sum << '\n';
}