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

int getValue(int node, std::vector<Node>& nodes) {
	Node& n{ nodes[node] };
	if (n.children.size() == 0) {
		int sum{};
		for (int meta : n.metadata) {
			sum += meta;
		}
		return sum;
	} else {
		int sum{};
		for (int meta : n.metadata) {
			if (meta > n.children.size()) continue;
			sum += getValue(n.children[meta - 1], nodes);
		}
		return sum;
	}
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
	
	std::cout << getValue(0, nodes) << '\n';
}