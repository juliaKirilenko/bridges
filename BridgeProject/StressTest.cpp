#include <vector>
#include <iostream>
#include "StressTest.hpp"


StressTest::StressTest(std::vector<std::vector<size_t>>& graph) {
	test_graph = graph;
	accuracy = 0.0;
}

void StressTest::dfs(size_t& current_node, size_t& parent) {
	visited[current_node] = true;
	for (size_t& neighbour : test_graph[current_node]) {
		if ((neighbour == parent) || (visited[neighbour]==true)) { continue; }
		dfs(neighbour, current_node);
	}
}

double StressTest::compOfConnect() {
	double connectivity_comps = 0;
	visited.resize(test_graph.size());
	for (size_t node = 0; node < test_graph.size(); ++node) {
		visited[node]=false;
	}
	for (size_t node = 0; node < test_graph.size(); ++node) {
		if (!visited[node]) {
			size_t no_parent = -1;
			dfs(node, no_parent);
			connectivity_comps++;
		}
	}
	return connectivity_comps;
}


float& StressTest::getAccuracyFromStressTest(std::vector<std::vector<std::pair<size_t, size_t>>>& bridges) {

	double components_before = compOfConnect();
	double all_components = components_before;
	
	for (auto& bridge : bridges) {
		for (auto& edge : bridge) {
			test_graph[edge.first].erase(std::find(test_graph[edge.first].begin(), test_graph[edge.first].end(), edge.second));
			test_graph[edge.second].erase(std::find(test_graph[edge.second].begin(), test_graph[edge.second].end(), edge.first));
		}
		double components_after = compOfConnect();
		all_components += components_after - components_before;
		for (auto& edge : bridge) {
			test_graph[edge.first].push_back(edge.second);
			test_graph[edge.second].push_back(edge.first);
		}
	}
	accuracy = all_components / (components_before + bridges.size());
	return accuracy;
}